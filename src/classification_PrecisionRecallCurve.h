#ifndef CLASSIFICATION_PRECISIONRECALLCURVE_H
#define CLASSIFICATION_PRECISIONRECALLCURVE_H

#include <Rcpp.h>
#include <vector>
#include <algorithm>
#include <numeric>
#include <memory>

#ifdef _OPENMP
  #include <omp.h>
#endif

#include "utilities_Package.h"

class prROC {
public:
    // Integration method enumeration
    enum IntegrationMethod { TRAPEZOIDAL = 0, STEP };

    /**
     * Compute class-wise average precision (AP) for each class.
     *
     * @param actual   Integer vector of true class labels.
     * @param response Numeric matrix of predicted scores.
     * @param method   Integration method (0 for trapezoidal, nonzero for step).
     * @param presorted  Set to true if each column in response is already sorted in descending order.
     * @param weights  Optional vector of observation weights.
     * @return         A numeric vector of average precision values (one per class).
     */
    static Rcpp::NumericVector class_wise(
        const Rcpp::IntegerVector& actual,
        const Rcpp::NumericMatrix& response,
        int method = TRAPEZOIDAL,
        bool presorted = false,
        const Rcpp::NumericVector* weights = nullptr) {
        
        const std::size_t n = actual.size();
        Rcpp::CharacterVector levels = actual.attr("levels");
        const int n_classes = levels.size();
        double (*updateArea)(double, double, double, double) =
            (method == TRAPEZOIDAL) ? trapezoid_area : step_area;
        Rcpp::NumericVector output(n_classes, 0.0);
        const int* ptr_actual = actual.begin();
        const double* ptr_weights = (weights != nullptr) ? weights->begin() : nullptr;

        #ifdef _OPENMP
        #pragma omp parallel for if(getUseOpenMP())
        #endif
        for (int c = 0; c < n_classes; ++c) {
            std::unique_ptr<std::size_t[]> idx_ptr = prepare_index(response, c, n, presorted);
            int class_label = c + 1;
            double positives = count_positives(ptr_actual, ptr_weights, idx_ptr.get(), n, class_label);
            double ap = 0.0;
            if (positives == 0.0) {
                output[c] = NA_REAL;
            } else {
                double tp = 0.0, fp = 0.0;
                double prev_recall = 0.0;
                double prev_precision = 1.0;  // By convention, precision is 1 when no predictions are made.
                for (std::size_t i = 0; i < n; i++) {
                    std::size_t id = idx_ptr[i];
                    double w = (ptr_weights != nullptr) ? ptr_weights[id] : 1.0;
                    if (ptr_actual[id] == class_label)
                        tp += w;
                    else
                        fp += w;
                    double recall = tp / positives;
                    double precision = (tp + fp > 0) ? (tp / (tp + fp)) : 1.0;
                    ap += updateArea(prev_recall, prev_precision, recall, precision);
                    prev_recall = recall;
                    prev_precision = precision;
                }
                output[c] = ap;
            }
        }
        output.attr("names") = levels;
        return output;
    }

    /**
     * Compute micro-average average precision by pooling all classes.
     *
     * @param actual    Integer vector of true class labels.
     * @param response  Numeric matrix of predicted scores.
     * @param method    Integration method (0 for trapezoidal, nonzero for step).
     * @param presorted Set to true if each column in response is already sorted.
     * @param weights   Optional vector of observation weights.
     * @return          The micro-average AP.
     */
    static double micro_average(
        const Rcpp::IntegerVector& actual,
        const Rcpp::NumericMatrix& response,
        int method = TRAPEZOIDAL,
        bool presorted = false,
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
                data[pos].score = *(p_response + i + n * c);
                data[pos].label = (act == (c + 1)) ? 1 : 0;
                data[pos].weight = w;
            }
        }
        std::sort(data.begin(), data.end(), [](const ScoreLabel &a, const ScoreLabel &b) {
            return a.score > b.score;
        });
        double positives = 0.0;
        #ifdef _OPENMP
        #pragma omp parallel for reduction(+:positives) if(getUseOpenMP())
        #endif
        for (std::size_t i = 0; i < data.size(); i++) {
            if (data[i].label == 1)
                positives += data[i].weight;
        }
        if (positives == 0.0)
            return NA_REAL;
        double (*updateArea)(double, double, double, double) =
            (method == TRAPEZOIDAL) ? trapezoid_area : step_area;
        return compute_ap(data, positives, updateArea);
    }

    /**
     * Compute macro-average average precision by averaging class-wise AP.
     *
     * @param actual    Integer vector of true class labels.
     * @param response  Numeric matrix of predicted scores.
     * @param method    Integration method (0 for trapezoidal, nonzero for step).
     * @param presorted Set to true if each column in response is already sorted.
     * @param weights   Optional vector of observation weights.
     * @return          The macro-average AP.
     */
    static double macro_average(
        const Rcpp::IntegerVector& actual,
        const Rcpp::NumericMatrix& response,
        int method = TRAPEZOIDAL,
        bool presorted = false,
        const Rcpp::NumericVector* weights = nullptr) {
        
        Rcpp::NumericVector classwise_ap = class_wise(actual, response, method, presorted, weights);
        double sum = 0.0;
        int count = 0;
        const double* p_ap = classwise_ap.begin();
        for (int i = 0; i < classwise_ap.size(); i++) {
            if (!Rcpp::NumericVector::is_na(p_ap[i])) {
                sum += p_ap[i];
                count++;
            }
        }
        if (count == 0)
            return NA_REAL;
        return sum / count;
    }

    /**
     * Generate a DataFrame representing the precision-recall curve for all classes.
     *
     * @param actual    Integer vector of true class labels.
     * @param response  Numeric matrix of predicted scores.
     * @param presorted Set to true if each column in response is already sorted.
     * @param weights   Optional vector of observation weights.
     * @return          A DataFrame with columns: threshold, level, label, recall, and precision.
     */
    static Rcpp::DataFrame pr_curve(
        const Rcpp::IntegerVector& actual,
        const Rcpp::NumericMatrix& response,
        bool presorted = false,
        const Rcpp::NumericVector* weights = nullptr) {
        
        int n = response.nrow();
        Rcpp::CharacterVector levels = actual.attr("levels");
        int num_classes = levels.size();
        int total_points = (n + 1) * num_classes;
        Rcpp::NumericVector thresholds_all(total_points);
        Rcpp::NumericVector recall_all(total_points);
        Rcpp::NumericVector precision_all(total_points);
        Rcpp::CharacterVector labels_all(total_points);
        Rcpp::IntegerVector levels_all(total_points);

        int idx = 0;
        const int* ptr_actual = actual.begin();
        const double* ptr_weights = (weights != nullptr) ? weights->begin() : nullptr;

        for (int c = 0; c < num_classes; ++c) {
            int class_label = c + 1;
            std::unique_ptr<std::size_t[]> idx_ptr = prepare_index(response, c, n, presorted);
            double positives = count_positives(ptr_actual, ptr_weights, idx_ptr.get(), n, class_label);
            double tp = 0.0, fp = 0.0;
            for (int i = 0; i <= n; ++i) {
                if (i == 0) {
                    thresholds_all[idx] = R_PosInf;
                } else {
                    int row = idx_ptr[i - 1];
                    thresholds_all[idx] = response(row, c);
                    double w = (ptr_weights != nullptr) ? ptr_weights[row] : 1.0;
                    if (ptr_actual[row] == class_label)
                        tp += w;
                    else
                        fp += w;
                }
                double recall_val = (positives > 0) ? (tp / positives) : 0.0;
                double precision_val = (tp + fp > 0) ? (tp / (tp + fp)) : 1.0;
                recall_all[idx] = recall_val;
                precision_all[idx] = precision_val;
                labels_all[idx] = levels[c];
                levels_all[idx] = class_label;
                ++idx;
            }
        }
        Rcpp::DataFrame output = Rcpp::DataFrame::create(
            Rcpp::Named("threshold") = thresholds_all,
            Rcpp::Named("level")     = levels_all,
            Rcpp::Named("label")     = labels_all,
            Rcpp::Named("recall")    = recall_all,
            Rcpp::Named("precision") = precision_all
        );
        output.attr("class") = Rcpp::CharacterVector::create("PrecisionRecall", "data.frame");
        return output;
    }

private:
    // Structure holding a score, its binary label, and its weight.
    struct ScoreLabel {
        double score;
        int label;
        double weight;
    };

    // Compute average precision (AP) from a sorted vector of ScoreLabel entries.
    static double compute_ap(
        const std::vector<ScoreLabel>& data,
        double positives,
        double (*updateArea)(double, double, double, double)) {
        
        double ap = 0.0;
        double tp = 0.0, fp = 0.0;
        double prev_recall = 0.0;
        double prev_precision = 1.0;
        for (std::size_t i = 0; i < data.size(); i++) {
            if (data[i].label == 1)
                tp += data[i].weight;
            else
                fp += data[i].weight;
            double recall = tp / positives;
            double precision = (tp + fp > 0) ? (tp / (tp + fp)) : 1.0;
            ap += updateArea(prev_recall, prev_precision, recall, precision);
            prev_recall = recall;
            prev_precision = precision;
        }
        return ap;
    }

    // Integration functions.
    static inline double trapezoid_area(double x1, double y1, double x2, double y2) {
        double width = (x2 - x1);
        double height = 0.5 * (y1 + y2);
        return width * height;
    }
    
    static inline double step_area(double x1, double y1, double x2, double y2) {
        double width = (x2 - x1);
        return width * y1;
    }
    
    // Prepare a sorted index array for the given response column.
    static inline std::unique_ptr<std::size_t[]> prepare_index(
        const Rcpp::NumericMatrix& response_matrix,
        int column,
        int n,
        bool presorted) {
        
        std::unique_ptr<std::size_t[]> idx(new std::size_t[n]);
        std::iota(idx.get(), idx.get() + n, 0);
        const double* col = &response_matrix(0, column);
        if (!presorted) {
            std::sort(idx.get(), idx.get() + n, [col](std::size_t a, std::size_t b) {
                return col[a] > col[b];
            });
        }
        return idx;
    }
    
    // Count the total positive weight for a given class.
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

    prROC() = delete;
    ~prROC() = delete;
};

#endif
