#ifndef CLASSIFICATION_RECEIVEROPERATORCURVE_H
#define CLASSIFICATION_RECEIVEROPERATORCURVE_H

#include <Rcpp.h>
#include <vector>
#include <algorithm>
#include <numeric>
#include <memory>

#ifdef _OPENMP
  #include <omp.h>
#endif

#include "utilities_Package.h"

/**
 * @class ROC
 * @brief A class for computing ROC curves and the area under the ROC curve (AUC) 
 *        for multi-class classification problems, with performance optimizations.
 *
 * The class provides:
 *   1) Class-wise AUC (one-vs-all).
 *   2) Micro-average AUC (global flattening).
 *   3) Macro-average AUC (average of class-wise AUC).
 *   4) A method to extract the entire ROC curve for each class, returned as an Rcpp::DataFrame.
 *
 * Optimizations:
 *   (1) Single pass to count positives and negatives together (instead of two passes).
 *   (2) Parallel sorting of columns when computing class-wise metrics.
 *   (3) Reuse a pre-allocated index array for each column (avoid repeated allocations).
 */
class ROC {
    public:
        // integration method
        enum integration_method { TRAPEZOIDAL = 0, STEP };

        /**
        * Compute class-wise AUC for each class (one-vs-all).
        *
        * Implements:
        *   - Parallel sorting for each column (item #2).
        *   - Reuse of index arrays (item #3.1).
        *   - Single pass for counting positives and negatives (item #1).
        *
        * @param actual    Integer vector of true class labels.
        * @param response  Numeric matrix of predicted scores.
        * @param method    Integration method (0 for trapezoidal, nonzero for step). 
        * @param presorted Set to true if each column in `response` is already sorted in descending order.
        * @param weights   Optional vector of observation weights.
        * @return          A numeric vector of AUC values (one per class).
        */
        static Rcpp::NumericVector class_wise(
            const Rcpp::IntegerVector& actual,
            const Rcpp::NumericMatrix& response,
            int method = TRAPEZOIDAL,
            bool presorted = false,
            const Rcpp::NumericVector* weights = nullptr) 
        {
            // 0) variable declarations
            Rcpp::CharacterVector levels = actual.attr("levels");
            const R_xlen_t n { actual.size() };
            const R_xlen_t n_classes { levels.size() };

            // integration method
            double (*update_area)(double, double, double, double) =
                (method == TRAPEZOIDAL) ? trapezoid_area : step_area;

            // output container
            Rcpp::NumericVector output(n_classes, 0.0);

            // pointers to data
            const int* ptr_actual { actual.begin() };
            const double* ptr_weights { (weights != nullptr) ? weights->begin() : nullptr };

            // 1) Create a pool of index arrays: one array per class
            //    so we can sort them in parallel without race conditions.
            std::vector< std::vector<std::size_t> > indices(n_classes, std::vector<std::size_t>(n));

            // 2) Populate and (optionally) parallel-sort
            #ifdef _OPENMP
            #pragma omp parallel for if(getUseOpenMP())
            #endif
            for (std::size_t c = 0; c < n_classes; c++) {
                // 2.1) Fill indices[c] with 0..n-1
                std::iota(indices[c].begin(), indices[c].end(), 0);

                // 2.2) If not presorted, sort this index array
                if (!presorted) {
                    const double* col_ptr = &response(0, c); // pointer to column c
                    std::sort(
                        indices[c].begin(),
                        indices[c].end(),
                        [col_ptr](std::size_t a, std::size_t b) {
                            return col_ptr[a] > col_ptr[b];
                        }
                    );
                }
            }

            // 3) Compute the AUC for each class
            #ifdef _OPENMP
            #pragma omp parallel for if(getUseOpenMP())
            #endif
            for (std::size_t c = 0; c < n_classes; ++c) {

                // 3.1) Single pass to count total positives & negatives
                //      for class_label c+1
                double positives { 0.0 };
                double negatives { 0.0 };
                {
                    int class_label = static_cast<int>(c + 1);
                    const auto& idxRef = indices[c];

                    for (std::size_t i = 0; i < n; i++) {
                        int actual_i = ptr_actual[idxRef[i]];
                        double w = (ptr_weights != nullptr) ? ptr_weights[idxRef[i]] : 1.0;

                        if (actual_i == class_label) {
                            positives += w;
                        } else {
                            negatives += w;
                        }
                    }
                }

                // 3.2) If no positives or no negatives, AUC is undefined
                if (positives == 0.0 || negatives == 0.0) {
                    output[c] = NA_REAL;
                    continue;
                }

                // 3.3) Compute AUC using incremental integration
                double auc = 0.0;
                double true_positive  { 0.0 };
                double false_positive { 0.0 };

                double previous_tpr { 0.0 };
                double previous_fpr { 0.0 };

                int class_label = static_cast<int>(c + 1);
                const auto& idxRef = indices[c];

                for (std::size_t i = 0; i < n; i++) {
                    std::size_t row_idx = idxRef[i];
                    double w = (ptr_weights != nullptr) ? ptr_weights[row_idx] : 1.0;

                    if (ptr_actual[row_idx] == class_label) {
                        true_positive += w;
                    } else {
                        false_positive += w;
                    }

                    double tpr = true_positive / positives;
                    double fpr = false_positive / negatives;

                    auc += update_area(previous_fpr, previous_tpr, fpr, tpr);

                    previous_tpr = tpr;
                    previous_fpr = fpr;
                }

                output[c] = auc;
            }

            // 4) Assign names to the output
            output.attr("names") = levels;

            // 5) Return result
            return output;
        }

        /**
        * Compute micro-average AUC by pooling all classes.
        *
        * This version also merges passes to count total positives/negatives in a single loop.
        * We do not have a separate "reuse array" across columns here, because we flatten
        * the entire matrix into one container. Sorting can still be parallelized if
        * a parallel sorting routine is used, but standard std::sort is typically serial.
        *
        * @param actual    Integer vector of true class labels.
        * @param response  Numeric matrix of predicted scores.
        * @param method    Integration method (0 for trapezoidal, nonzero for step).
        * @param presorted Unused in micro-average because we flatten scores from all columns.
        * @param weights   Optional vector of observation weights.
        * @return          The micro-average AUC.
        */
        static double micro_average(
            const Rcpp::IntegerVector& actual,
            const Rcpp::NumericMatrix& response,
            int method = TRAPEZOIDAL,
            bool /* presorted */ = false,
            const Rcpp::NumericVector* weights = nullptr) 
        {
            // 0) variable declarations
            const R_xlen_t n { actual.size() };
            const R_xlen_t n_classes { response.ncol() };

            // integration method
            double (*update_area)(double, double, double, double) =
                (method == TRAPEZOIDAL) ? trapezoid_area : step_area;

            // Flatten the matrix: we have n * n_classes scores
            std::vector<threshold_container> container(n * n_classes);

            const int* ptr_actual { actual.begin() };
            const double* ptr_response { response.begin() };
            const double* ptr_weights { (weights != nullptr) ? weights->begin() : nullptr };

            // 1) Flatten in one pass
            #ifdef _OPENMP
                #pragma omp parallel for if(getUseOpenMP())
            #endif
            for (std::size_t i = 0; i < n; i++) {
                double w = (ptr_weights != nullptr) ? ptr_weights[i] : 1.0;
                int actual_i = ptr_actual[i];

                for (std::size_t c = 0; c < n_classes; c++) {
                    std::size_t idx = i * n_classes + c;

                    container[idx].score  = *(ptr_response + i + n * c);
                    container[idx].label  = ((int)(c + 1) == actual_i) ? 1 : 0;
                    container[idx].weight = w;
                }
            }

            // 2) Sort container by descending scores
            std::sort(
                container.begin(),
                container.end(),
                [](const threshold_container &a, const threshold_container &b) {
                    return a.score > b.score;
                }
            );

            // 3) Single pass to count total positives & negatives
            double positives { 0.0 };
            double negatives { 0.0 };
            for (auto &tc : container) {
                if (tc.label == 1) {
                    positives += tc.weight;
                } else {
                    negatives += tc.weight;
                }
            }
            if (positives == 0.0 || negatives == 0.0) {
                return NA_REAL;
            }

            // 4) Compute micro-average AUC
            double auc { 0.0 };
            double true_positive  { 0.0 };
            double false_positive { 0.0 };
            double previous_tpr { 0.0 };
            double previous_fpr { 0.0 };

            for (auto &tc : container) {
                if (tc.label == 1) {
                    true_positive += tc.weight;
                } else {
                    false_positive += tc.weight;
                }
                double tpr = true_positive / positives;
                double fpr = false_positive / negatives;

                auc += update_area(previous_fpr, previous_tpr, fpr, tpr);
                previous_tpr = tpr;
                previous_fpr = fpr;
            }

            return auc;
        }

        /**
        * Compute macro-average AUC by averaging class-wise AUC.
        *
        * @param actual    Integer vector of true class labels.
        * @param response  Numeric matrix of predicted scores.
        * @param method    Integration method (0 for trapezoidal, nonzero for step).
        * @param presorted Set to true if each column in `response` is already sorted.
        * @param weights   Optional vector of observation weights.
        * @return          The macro-average AUC.
        */
        static double macro_average(
            const Rcpp::IntegerVector& actual,
            const Rcpp::NumericMatrix& response,
            int method = TRAPEZOIDAL,
            bool presorted = false,
            const Rcpp::NumericVector* weights = nullptr) 
        {
            // compute class-wise AUC
            Rcpp::NumericVector classwise_auc = class_wise(
                actual, response, method, presorted, weights);

            double sum { 0.0 };
            std::size_t count { 0 };

            const double* ptr_classwise_auc = classwise_auc.begin();
            for (std::size_t i = 0; i < classwise_auc.size(); i++) {
                if (!Rcpp::NumericVector::is_na(ptr_classwise_auc[i])) {
                    sum += ptr_classwise_auc[i];
                    count++;
                }
            }
            if (count == 0) {
                return NA_REAL;
            }
            return sum / count;
        }

        /**
        * Generate a DataFrame representing the ROC curve for all classes.
        *
        * @param actual     Integer vector of true class labels.
        * @param response   Numeric matrix of predicted scores.
        * @param presorted  Set to true if each column in `response` is already sorted in descending order.
        * @param weights    Optional vector of observation weights.
        * @param thresholds Optional user-specified vector of threshold values.
        *
        * @return DataFrame with columns: threshold, level, label, tpr, fpr.
        */
        static Rcpp::DataFrame roc_curve(
            const Rcpp::IntegerVector& actual,
            const Rcpp::NumericMatrix& response,
            bool presorted = false,
            const Rcpp::NumericVector* weights = nullptr,
            const Rcpp::NumericVector* thresholds = nullptr) 
        {
            // 0) variable declarations
            Rcpp::CharacterVector levels = actual.attr("levels");
            const R_xlen_t n { response.nrow() };
            const R_xlen_t n_classes { response.ncol() };

            const R_xlen_t data_points_per_class {
                (thresholds != nullptr) ? thresholds->size() + 2 : (n + 1)
            };
            const R_xlen_t total_data_points = data_points_per_class * n_classes;

            const int* ptr_actual { actual.begin() };
            const double* ptr_weights { (weights != nullptr) ? weights->begin() : nullptr };

            // output containers
            Rcpp::NumericVector thresholds_vector(total_data_points);
            Rcpp::NumericVector tpr_vector(total_data_points);
            Rcpp::NumericVector fpr_vector(total_data_points);
            Rcpp::CharacterVector label_vector(total_data_points);
            Rcpp::IntegerVector levels_vector(total_data_points);

            // we again reuse an index pool
            std::vector< std::vector<std::size_t> > indices(n_classes, std::vector<std::size_t>(n));

            // 1) Prepare sorted indices for each column (possibly in parallel)
            #ifdef _OPENMP
            #pragma omp parallel for if(getUseOpenMP())
            #endif
            for (std::size_t c = 0; c < n_classes; c++) {
                std::iota(indices[c].begin(), indices[c].end(), 0);
                if (!presorted) {
                    const double* col_ptr = &response(0, c);
                    std::sort(
                        indices[c].begin(),
                        indices[c].end(),
                        [col_ptr](std::size_t a, std::size_t b) {
                            return col_ptr[a] > col_ptr[b];
                        }
                    );
                }
            }

            // 2) Build the ROC curve
            std::size_t idx { 0 };

            for (std::size_t c = 0; c < n_classes; ++c) {

                // single pass to count total positives & negatives
                double positives { 0.0 };
                double negatives { 0.0 };
                {
                    int class_label = static_cast<int>(c + 1);
                    const auto& idxRef = indices[c];
                    for (std::size_t i = 0; i < n; i++) {
                        double w = (ptr_weights != nullptr) ? ptr_weights[idxRef[i]] : 1.0;
                        if (ptr_actual[idxRef[i]] == class_label) {
                            positives += w;
                        } else {
                            negatives += w;
                        }
                    }
                }

                double true_positive { 0.0 };
                double false_positive { 0.0 };

                if (thresholds != nullptr) {
                    // 2.1) With user-provided thresholds

                    // start with +Inf => TPR=0, FPR=0
                    thresholds_vector[idx] = R_PosInf;
                    tpr_vector[idx] = 0.0;
                    fpr_vector[idx] = 0.0;
                    label_vector[idx] = levels[c];
                    levels_vector[idx] = (int)(c + 1);
                    ++idx;

                    const double* ptr_thresholds = thresholds->begin();
                    std::size_t j { 0 };
                    const auto& idxRef = indices[c];
                    int class_label = (int)(c + 1);

                    for (std::size_t k = 0; k < thresholds->size(); ++k) {
                        double threshold_k = ptr_thresholds[k];

                        // move j while score >= threshold_k
                        while (j < (std::size_t)n &&
                               response(idxRef[j], c) >= threshold_k) 
                        {
                            double w = (ptr_weights != nullptr) ? ptr_weights[idxRef[j]] : 1.0;
                            if (ptr_actual[idxRef[j]] == class_label) {
                                true_positive += w;
                            } else {
                                false_positive += w;
                            }
                            ++j;
                        }

                        double tpr = (positives > 0.0) ? (true_positive / positives) : 0.0;
                        double fpr = (negatives > 0.0) ? (false_positive / negatives) : 0.0;

                        thresholds_vector[idx] = threshold_k;
                        tpr_vector[idx] = tpr;
                        fpr_vector[idx] = fpr;
                        label_vector[idx] = levels[c];
                        levels_vector[idx] = class_label;
                        ++idx;
                    }

                    // end with -Inf => TPR=1, FPR=1 (if positives/negatives > 0)
                    thresholds_vector[idx] = R_NegInf;
                    double tpr = (positives > 0.0) ? (true_positive / positives) : 0.0;
                    double fpr = (negatives > 0.0) ? (false_positive / negatives) : 0.0;
                    tpr_vector[idx] = tpr;
                    fpr_vector[idx] = fpr;
                    label_vector[idx] = levels[c];
                    levels_vector[idx] = class_label;
                    ++idx;

                } else {
                    // 2.2) Without user-provided thresholds
                    //      we add (n+1) points from +Inf down to last score

                    const auto& idxRef = indices[c];
                    int class_label = (int)(c + 1);

                    for (std::size_t i = 0; i <= (std::size_t)n; i++) {
                        if (i == 0) {
                            thresholds_vector[idx] = R_PosInf;
                        } else {
                            std::size_t row_idx = idxRef[i - 1];
                            thresholds_vector[idx] = response(row_idx, c);

                            double w = (ptr_weights != nullptr) ? ptr_weights[row_idx] : 1.0;
                            if (ptr_actual[row_idx] == class_label) {
                                true_positive += w;
                            } else {
                                false_positive += w;
                            }
                        }

                        double tpr = (positives > 0.0) ? (true_positive / positives) : 0.0;
                        double fpr = (negatives > 0.0) ? (false_positive / negatives) : 0.0;

                        tpr_vector[idx] = tpr;
                        fpr_vector[idx] = fpr;
                        label_vector[idx] = levels[c];
                        levels_vector[idx] = class_label;
                        ++idx;
                    }
                }
            }

            // 3) Construct the DataFrame
            Rcpp::DataFrame output = Rcpp::DataFrame::create(
                Rcpp::Named("threshold") = thresholds_vector,
                Rcpp::Named("level")     = levels_vector,
                Rcpp::Named("label")     = label_vector,
                Rcpp::Named("tpr")       = tpr_vector,
                Rcpp::Named("fpr")       = fpr_vector
            );
            output.attr("class") = Rcpp::CharacterVector::create("ROC", "data.frame");

            return output;
        }


    private:
        /**
        * @brief Container for storing score/label/weight, used primarily for micro-average.
        */
        struct threshold_container {
            double score;
            int label;
            double weight;
        };

        /**
        * @brief Compute area increment using the trapezoidal rule.
        *
        * @param x1 The FPR at the previous point.
        * @param y1 The TPR at the previous point.
        * @param x2 The FPR at the current point.
        * @param y2 The TPR at the current point.
        * @return   The incremental area under the TPR-FPR curve.
        */
        static inline double trapezoid_area(
            double x1,
            double y1,
            double x2,
            double y2) 
        {
            double width  = (x2 - x1);
            double height = 0.5 * (y1 + y2);
            return width * height;
        }

        /**
        * @brief Compute area increment using the step method (no interpolation).
        *
        * @param x1 The FPR at the previous point.
        * @param y1 The TPR at the previous point (unused in final calc).
        * @param x2 The FPR at the current point.
        * @param y2 The TPR at the current point.
        * @return   The incremental area under the curve.
        */
        static inline double step_area(
            double x1,
            double /*y1*/,
            double x2,
            double y2) 
        {
            double width = (x2 - x1);
            return width * y2;
        }

        // prevent direct construction
        ROC()  = delete;
        ~ROC() = delete;
};

#endif 
