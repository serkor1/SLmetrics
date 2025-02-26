#ifndef CLASSIFICATION_AREAUNDERTHECURVE_H
#define CLASSIFICATION_AREAUNDERTHECURVE_H

#include <Rcpp.h>
#include <vector>
#include <algorithm>
#include <numeric>
#include <memory>
#ifdef _OPENMP
  #include <omp.h>
#endif
#include "utilities_Package.h"

class ROC {
    public:

    /**
    * @brief
    * 
    */
    static Rcpp::NumericVector class_wise(
        const Rcpp::IntegerVector& actual,
        const Rcpp::NumericMatrix& response,
        int method = 0,
        bool ordered = false,
        const Rcpp::NumericVector* weights = nullptr) {
                    
            const std::size_t n = actual.size();
            Rcpp::CharacterVector levels = actual.attr("levels");
            const int n_classes = levels.size();
            double (*updateArea)(double, double, double, double) = (method == 0) ? trapeziod_area : step_area;
            Rcpp::NumericVector output(n_classes, 0.0);
            const int* ptr_actual = actual.begin();
            const double* ptr_weights = (weights != nullptr) ? weights->begin() : nullptr;
            
            double total_weight = (ptr_weights != nullptr) 
                                ? std::accumulate(ptr_weights, ptr_weights + n, 0.0)
                                : static_cast<double>(n);
            
            #ifdef _OPENMP
                #pragma omp parallel for if(getUseOpenMP())
            #endif
            for (int c = 0; c < n_classes; ++c) {
                std::unique_ptr<std::size_t[]> idx_ptr = prepare_index(response, c, n, ordered);
                int class_label = c + 1;

                double positives = count_positives(ptr_actual, ptr_weights, idx_ptr.get(), n, class_label);
                double negatives = total_weight - positives;
                
                double area = 0.0;
                if (positives == 0.0 || negatives == 0.0) {
                    output[c] = NA_REAL;
                } else {
                    double tp = 0.0, fp = 0.0;
                    double prev_tpr = 0.0, prev_fpr = 0.0;
                    std::size_t* idx = idx_ptr.get();
                    for (std::size_t i = 0; i < n; i++) {
                        std::size_t id = *(idx + i);
                        // Use weight=1 if no weights provided.
                        double w = (ptr_weights != nullptr) ? ptr_weights[id] : 1.0;
                        if (*(ptr_actual + id) == class_label)
                            tp += w;
                        else
                            fp += w;
                        double cur_tpr = tp / positives;
                        double cur_fpr = fp / negatives;
                        area += updateArea(prev_fpr, prev_tpr, cur_fpr, cur_tpr);
                        prev_tpr = cur_tpr;
                        prev_fpr = cur_fpr;
                    }
                    output[c] = area;
                }
            }

            output.attr("names") = levels;
            return output;
        }

    static double micro_average(
        const Rcpp::IntegerVector& actual,
        const Rcpp::NumericMatrix& response,
        int method = 0,
        bool ordered = false,
        const Rcpp::NumericVector* weights = nullptr) {

            int n = actual.size();
            int n_classes = response.ncol();

            std::vector<ScoreLabel> data(n * n_classes);
            const int* p_actual = actual.begin();
            const double* p_response = response.begin();
            const double* p_weights = (weights != nullptr) ? weights->begin() : nullptr;
            
            #ifdef _OPENMP
                #pragma omp parallel for if(getUseOpenMP())
            #endif
            for (int i = 0; i < n; i++) {
                int act = p_actual[i];
                double w = (p_weights != nullptr) ? p_weights[i] : 1.0;
                for (int c = 0; c < n_classes; c++) {
                    int pos = i * n_classes + c;
                    data[pos].score  = *(p_response + i + n * c);
                    data[pos].label  = (act == (c + 1)) ? 1 : 0;
                    data[pos].weight = w;
                }
            }
            
            std::sort(data.begin(), data.end(), [](const ScoreLabel &a, const ScoreLabel &b) {
                return a.score > b.score;
            });
            
            double positives = 0.0, negatives = 0.0;
            #ifdef _OPENMP
                #pragma omp parallel for reduction(+:positives, negatives) if(getUseOpenMP())
            #endif
            for (std::size_t i = 0; i < data.size(); i++) {
                if (data[i].label == 1)
                    positives += data[i].weight;
                else
                    negatives += data[i].weight;
            }
            if (positives == 0.0 || negatives == 0.0)
                return NA_REAL;
                
            double (*updateArea)(double, double, double, double) = (method == 0) ? trapeziod_area : step_area;
            return compute_auc(data, positives, negatives, updateArea);
    }

    static double macro_average(
        const Rcpp::IntegerVector& actual,
        const Rcpp::NumericMatrix& response,
        int method = 0,
        bool ordered = false,
        const Rcpp::NumericVector* weights = nullptr) {
        
            Rcpp::NumericVector classwise_auc = class_wise(actual, response, method, ordered, weights);
            double sum = 0.0;
            int count = 0;
            const double* p_auc = classwise_auc.begin();
            for (int i = 0; i < classwise_auc.size(); i++) {
                if (!Rcpp::NumericVector::is_na(*(p_auc + i))) {
                    sum += *(p_auc + i);
                    count++;
                }
            }
            if (count == 0)
                return NA_REAL;
            return sum / count;
    }

    static Rcpp::DataFrame roc_curve(
        const Rcpp::IntegerVector& actual,
        const Rcpp::NumericMatrix& response,
        bool ordered = false,
        const Rcpp::NumericVector* weights = nullptr,
        const Rcpp::NumericVector* thresholds = nullptr) {

            int n = response.nrow();
            Rcpp::CharacterVector levels = actual.attr("levels");
            int num_classes = levels.size();
            int points_per_class = (thresholds != nullptr) ? thresholds->size() + 2: (n + 1);
            int total_points = points_per_class * num_classes;

            Rcpp::NumericVector thresholds_all(total_points);
            Rcpp::NumericVector tpr_all(total_points);
            Rcpp::NumericVector fpr_all(total_points);
            Rcpp::CharacterVector labels_all(total_points);
            Rcpp::IntegerVector levels_all(total_points);

            int idx = 0;
            const int* ptr_actual = actual.begin();
            const double* ptr_weights = (weights != nullptr) ? weights->begin() : nullptr;

            double total_weight = (ptr_weights != nullptr)
                                ? std::accumulate(ptr_weights, ptr_weights + n, 0.0)
                                : static_cast<double>(n);

            const double* ptr_thresholds = (thresholds != nullptr) ? thresholds->begin() : nullptr;

            for (int c = 0; c < num_classes; ++c) {
                int class_label = c + 1;
                std::unique_ptr<std::size_t[]> idx_ptr = prepare_index(response, c, n, ordered);

                double positives = count_positives(ptr_actual, ptr_weights, idx_ptr.get(), n, class_label);
                double negatives = (ptr_weights != nullptr) ? (total_weight - positives) : (n - positives);

                double tp = 0.0, fp = 0.0;
                if (thresholds != nullptr) {

                    thresholds_all[idx] = R_PosInf;
                    tpr_all[idx] = 0.0;
                    fpr_all[idx] = 0.0;
                    labels_all[idx] = levels[c];
                    levels_all[idx] = class_label;
                    ++idx;

                    int j = 0; 
                    for (int k = 0; k < thresholds->size(); ++k) {
                        double thr = ptr_thresholds[k]; // current threshold value
                        while (j < n && response(idx_ptr.get()[j], c) >= thr) {
                            int row = idx_ptr.get()[j];
                            double w = (ptr_weights != nullptr) ? ptr_weights[row] : 1.0;
                            if (ptr_actual[row] == class_label)
                                tp += w;
                            else
                                fp += w;
                            ++j;
                        }
                        thresholds_all[idx] = thr;
                        tpr_all[idx] = (positives > 0) ? (tp / positives) : 0.0;
                        fpr_all[idx] = (negatives > 0) ? (fp / negatives) : 0.0;
                        labels_all[idx] = levels[c];
                        levels_all[idx] = class_label;
                        ++idx;
                    }

                    thresholds_all[idx] = R_NegInf;
                    tpr_all[idx] = 1.0;
                    fpr_all[idx] = 1.0;
                    labels_all[idx] = levels[c];
                    levels_all[idx] = class_label;
                    ++idx;

                } else {
                    for (int i = 0; i <= n; ++i) {
                        if (i == 0) {
                            thresholds_all[idx] = R_PosInf;
                        } else {
                            int row = idx_ptr.get()[i - 1];
                            thresholds_all[idx] = response(row, c);
                        }
                        
                        if (i > 0) {
                            int row = idx_ptr.get()[i - 1];
                            double w = (ptr_weights != nullptr) ? ptr_weights[row] : 1.0;
                            if (ptr_actual[row] == class_label)
                                tp += w;
                            else
                                fp += w;
                        }
                        double cur_tpr = (positives > 0) ? (tp / positives) : 0.0;
                        double cur_fpr = (negatives > 0) ? (fp / negatives) : 0.0;
                        
                        tpr_all[idx] = cur_tpr;
                        fpr_all[idx] = cur_fpr;
                        labels_all[idx] = levels[c];
                        levels_all[idx] = class_label;
                        ++idx;
                    }
                }
            }
            
            Rcpp::DataFrame output = Rcpp::DataFrame::create(
                Rcpp::Named("threshold") = thresholds_all,
                Rcpp::Named("level")     = levels_all,
                Rcpp::Named("label")     = labels_all,
                Rcpp::Named("fpr")       = fpr_all,
                Rcpp::Named("tpr")       = tpr_all
            );

            output.attr("class") = Rcpp::CharacterVector::create("ROC", "data.frame");
            
            return output;
        }


    private:
        // Structure holding a score, its binary label, and its weight.
        struct ScoreLabel {
            double score;
            int label;
            double weight;
        };

        // Compute AUC from a sorted vector of ScoreLabel entries.
        static double compute_auc(
            const std::vector<ScoreLabel>& data,
            double positives, double negatives,
            double (*updateArea)(double, double, double, double)) {
            
            double area = 0.0;
            double tp = 0.0, fp = 0.0;
            double prev_tpr = 0.0, prev_fpr = 0.0;
            for (std::size_t i = 0; i < data.size(); i++) {
                if (data[i].label == 1)
                    tp += data[i].weight;
                else
                    fp += data[i].weight;
                double cur_tpr = tp / positives;
                double cur_fpr = fp / negatives;
                area += updateArea(prev_fpr, prev_tpr, cur_fpr, cur_tpr);
                prev_tpr = cur_tpr;
                prev_fpr = cur_fpr;
            }
            return area;
        }

        static inline double trapeziod_area(double x1, double y1, double x2, double y2) {
            double width  = (x2 - x1);
            double height = 0.5 * (y1 + y2);
            return width * height;
        }
        static inline double step_area(double x1, double y1, double x2, double y2) {
            double width  = (x2 - x1);
            double height = y1;
            return width * height;
        }

        static inline std::unique_ptr<std::size_t[]> prepare_index(
            const Rcpp::NumericMatrix& response_matrix,
            int column,
            int n,
            bool ordered) {
            
            std::unique_ptr<std::size_t[]> idx(new std::size_t[n]);
            std::iota(idx.get(), idx.get() + n, 0);
            const double* col = &response_matrix(0, column);
            if (!ordered) {
                std::sort(idx.get(), idx.get() + n, [col](std::size_t a, std::size_t b) {
                    return col[a] > col[b];
                });
            }
            return idx;
        }

        static inline double count_positives(
            const int* ptr_actual,
            const double* ptr_weights,
            const std::size_t* idx,
            int n,
            int class_label) {
            
            double positives = 0.0;
            for (int i = 0; i < n; i++) {
                if (ptr_actual[idx[i]] == class_label)
                    positives += (ptr_weights != nullptr) ? ptr_weights[idx[i]] : 1.0;
            }
            return positives;
        }

        ROC() = delete;
        ~ROC() = delete;
};

#endif