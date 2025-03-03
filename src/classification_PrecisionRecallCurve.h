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
        // integration method
        enum integration_method { TRAPEZOIDAL = 0, STEP };

        /**
        * Compute class-wise average precision (AP) for each class.
        *
        * @param actual   Integer vector of true class labels.
        * @param response Numeric matrix of predicted scores.
        * @param method   Integration method (0 for trapezoidal, nonzero for step). Note: step method is equivalent to {scikit-learn}, ie. no interpolation.
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
                // start of function

                // 0) variable declarations
                // common (fixed) parameters:
                Rcpp::CharacterVector levels = actual.attr("levels");
                const R_xlen_t n { actual.size() };
                const R_xlen_t n_classes { levels.size() };

                // integration method
                double (*update_area)(double, double, double, double) =
                    (method == TRAPEZOIDAL) ? trapezoid_area : step_area;

                // output container
                Rcpp::NumericVector output(n_classes, 0.0);

                // pointers to weights (if passed)
                // and actual values
                const int* ptr_actual { actual.begin() };
                const double* ptr_weights { (weights != nullptr) ? weights->begin() : nullptr };
                
                // 1) calculate average precision
                // (area under the curve) for each
                // class c
                #ifdef _OPENMP
                    #pragma omp parallel for if(getUseOpenMP())
                #endif
                for (std::size_t c = 0; c < n_classes; ++c) {

                    // 1.1) create smart pointer
                    // to the sorted values
                    //
                    // NOTE: This is a smart pointer - so it deletes
                    // itself to avoid memory leaks
                    std::unique_ptr<std::size_t[]> ptr_idx{ prepare_index(response, c, n, presorted) };

                    // 1.2) define class label
                    // and add one - C++ is 0 indexed, factors are 
                    // are 1 indexed
                    std::size_t class_label { c + 1 };

                    // 1.3) count number
                    // of positives
                    double positives { count_positives(ptr_actual, ptr_weights, ptr_idx.get(), n, class_label) };

                    // 1.4) declare average precision
                    // initialized to 0.0 for each class.
                    double average_precision{ 0.0 };

                    // 1.5) calculate
                    // average precision
                    // for each class
                    if (positives == 0.0) {
                        output[c] = NA_REAL;
                    } else {

                        // 1.5.1) declare and initialize
                        // auxiliary values used for the 
                        // calculations
                        //
                        // NOTE: recall starts at 0.0, and precision
                        // starts at 1.0 by convention
                        double true_positive { 0.0 };
                        double false_positive { 0.0 };
                        double previous_recall { 0.0 };
                        double previous_precision { 1.0 };

                        // 1.5.2) calculate the
                        // values for each container
                        for (std::size_t i = 0; i < n; i++) {

                            // 1.5.2.1) extract the
                            // index pointer, and store
                            // as idx
                            std::size_t idx { ptr_idx[i] };

                            // 1.5.2.2) calculate the
                            // incrementing value
                            //
                            // NOTE: if the weightes are passed
                            // then each true_positive or false_positive gets incremented by
                            // w_i, ie. the weight at index i. Otherwise it just gets incremented
                            // by 1.0
                            double w{(ptr_weights != nullptr) ? ptr_weights[idx] : 1.0};
                            if (ptr_actual[idx] == class_label) {
                                true_positive += w;
                            } else {
                                false_positive += w;
                            }

                            // 1.5.2.3) calculate
                            // recall and precision
                            // 
                            // NOTE: There is already a guard
                            // against 0 positives
                            double recall { true_positive / positives };
                            double precision { (true_positive + false_positive > 0) ? (true_positive / (true_positive + false_positive)) : 1.0 };
                            
                            // 1.5.2.4) add to average_precision
                            // container and store the recall and
                            // prevision for the next iteration.
                            average_precision += update_area(previous_recall, previous_precision, recall, precision);
                            previous_recall = recall;
                            previous_precision = precision;
                        }

                        // 1.6) store in output
                        output[c] = average_precision;
                    }
                }
                        
                // 2) set names attribute
                // so the returned values are
                // named
                output.attr("names") = levels;

                // 3) return the output
                return output;
            // end of function
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
                    // start of function

                    // 0) variable declarations
                    // common (fixed) parameters:
                    const R_xlen_t n { actual.size() };
                    const R_xlen_t n_classes { response.ncol() };

                    // integration method
                    double (*update_area)(double, double, double, double) =
                        (method == TRAPEZOIDAL) ? trapezoid_area : step_area;

                    // output container
                    Rcpp::NumericVector output(n_classes, 0.0);

                    // pointers to weights (if passed)
                    // and actual-values
                    const int* ptr_actual { actual.begin() };
                    const double* ptr_response { response.begin() };
                    const double* ptr_weights { (weights != nullptr) ? weights->begin() : nullptr };

                    // container for aggregating
                    // true and false positives
                    std::vector<threshold_container> container(n * n_classes);

                    // variable for aggregating
                    // positives
                    double positives { 0.0 };
                    
                    // 1) flatten response matrix
                    // by aggregating values for each
                    // threshold
                    #ifdef _OPENMP
                        #pragma omp parallel for if(getUseOpenMP())
                    #endif
                    for (std::size_t i = 0; i < n; i++) {

                        // 1.1) extract actual
                        // value (unsorted)
                        R_xlen_t actual_i { ptr_actual[i] };

                        // 1.2) calculate weight
                        // NOTE: if weighted the ith index
                        // of the weights are used. 1.0 otherwise
                        // (regular counting)
                        double w { (ptr_weights != nullptr) ? ptr_weights[i] : 1.0 };

                        // 1.3) loop through all
                        // all classes and populate
                        // the container
                        for (std::size_t c = 0; c < n_classes; c++) {

                            // 1.3.1) calculate container
                            // index
                            std::size_t idx { i * n_classes + c };

                            // 1.3.2) store values in the
                            // container by idx
                            container[idx].score  = *(ptr_response + i + n * c);
                            container[idx].label  = (actual_i == (c + 1)) ? 1 : 0;
                            container[idx].weight = w;
                        }
                    }

                    // 1.1) sort the container
                    // in descending order
                    std::sort(
                        container.begin(),
                        container.end(), 
                        [](const threshold_container &a, const threshold_container &b) { return a.score > b.score;}
                    );

                    // 2) calculate positives
                    // in the contaiener
                    #ifdef _OPENMP
                        #pragma omp parallel for reduction(+:positives) if(getUseOpenMP())
                    #endif
                    for (std::size_t i = 0; i < container.size(); i++) {
                        if (container[i].label == 1)
                            positives += container[i].weight;
                    }

                    // 2.1) if there is no
                    // positives return NA
                    if (positives == 0.0)
                        return NA_REAL;

                    // 3) calculate (micro) averaged
                    // precision and return
                    return compute_average_precision(container, positives, update_area);
                    
                // end of function
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
                    // start of function

                    // 0) variable declarations

                    // calculate class-wise average
                    // precision (AUC)
                    Rcpp::NumericVector classwise_average_precision = class_wise(actual, response, method, presorted, weights);

                    // sum and indices count variables
                    double sum { 0.0 };
                    std::size_t count { 0 };

                    // pointer to the class-wise
                    // average precision
                    const double* ptr_class_wise_average_precision = classwise_average_precision.begin();

                    // 1) calculate the sum
                    // and count (N)
                    for (std::size_t i = 0; i < classwise_average_precision.size(); i++) {
                        if (!Rcpp::NumericVector::is_na(ptr_class_wise_average_precision[i])) {
                            sum += ptr_class_wise_average_precision[i];
                            count++;
                        }
                    }

                    // 1.1) if the count
                    // is 0, ie. no REAL values
                    // return NA
                    if (count == 0)
                        return NA_REAL;

                    // 2) return the 
                    // (macro) averaged precision
                    // and return
                    return sum / count;

            // end of function
            }

            /**
            * Generate a containerFrame representing the precision-recall curve for all classes.
            *
            * @param actual    Integer vector of true class labels.
            * @param response  Numeric matrix of predicted scores.
            * @param presorted Set to true if each column in response is already sorted.
            * @param weights   Optional vector of observation weights.
            * @return          A containerFrame with columns: threshold, level, label, recall, and precision.
            */
            static Rcpp::DataFrame pr_curve(
                const Rcpp::IntegerVector& actual,
                const Rcpp::NumericMatrix& response,
                bool presorted = false,
                const Rcpp::NumericVector* weights = nullptr,
                const Rcpp::NumericVector* thresholds = nullptr) {
                    // start of function

                    // 0) variable declarations
                    // common (fixed) parameters:
                    Rcpp::CharacterVector levels = actual.attr("levels");
                    const R_xlen_t n { response.nrow() };
                    const R_xlen_t n_classes { response.ncol() };

                    // derived parameters
                    const R_xlen_t data_points_per_class { (thresholds != nullptr) ? thresholds->size() + 2 : (n + 1) };
                    const R_xlen_t total_data_points { data_points_per_class * n_classes };

                    // pointers to weights (if passed)
                    // and actual values
                    const int* ptr_actual { actual.begin() };
                    const double* ptr_weights { (weights != nullptr) ? weights->begin() : nullptr };

                    // containers for all
                    // values
                    Rcpp::NumericVector thresholds_vector(total_data_points);
                    Rcpp::NumericVector recall_vector(total_data_points);
                    Rcpp::NumericVector precision_vector(total_data_points);
                    Rcpp::CharacterVector label_vector(total_data_points);
                    Rcpp::IntegerVector levels_vector(total_data_points);
                    
                    // 1) construct the class-wise
                    // precision and recalls
                    std::size_t idx { 0 };
                    for (std::size_t c = 0; c < n_classes; ++c) {

                        // 1.1) create smart pointer
                        // to the sorted values
                        //
                        // NOTE: This is a smart pointer - so it deletes
                        // itself to avoid memory leaks
                        std::unique_ptr<std::size_t[]> ptr_idx{ prepare_index(response, c, n, presorted) };

                        // 1.2) define class label
                        // and add one - C++ is 0 indexed, factors are 
                        // are 1 indexed
                        std::size_t class_label { c + 1 };

                        // 1.3) count number
                        // of positives
                        double positives { count_positives(ptr_actual, ptr_weights, ptr_idx.get(), n, class_label) };

                        // 1.4) declare and initialize
                        // auxiliary values used for the 
                        // calculations
                        double true_positive { 0.0 };
                        double false_positive { 0.0 };

                        // 1.5) calculate values
                        // conditional on wether
                        // thresholds are passed
                        if (thresholds != nullptr) {
                            // With thresholds; 
                            // NOTE: the header numbering resets
                            // in the no-thresholds branch

                            // 1.5.1) initialize
                            // each vector by class
                            // by adding arbitrary thresholds 
                            // and values to ensure pretty precision-recall
                            // curve
                            thresholds_vector[idx] = R_PosInf;
                            recall_vector[idx] = 0.0;
                            precision_vector[idx] = 1.0;
                            label_vector[idx] = levels[c];
                            levels_vector[idx] = class_label;

                            // 1.5.1.1) iterate 
                            // to the next index 
                            ++idx;

                            // 1.5.2) loop through
                            // the thresholds and populate
                            // the vectors
                            std::size_t j { 0 };
                            const double* ptr_thresholds { thresholds->begin() };
                            for (std::size_t k = 0; k < thresholds->size(); ++k) {

                                // 1.5.2.1) extract the
                                // ith threshold
                                double threshold_i { ptr_thresholds[k] };

                                // 1.5.2.2) aggregate
                                // all values up the the
                                // ith-threshold
                                while (j < n && response(ptr_idx.get()[j], c) >= threshold_i) {
                                    // 1.5.2.2.1) extract
                                    // the row index
                                    std::size_t row_idx { ptr_idx.get()[j] };

                                    // 1.5.2.2.2) calculate
                                    // the weight of the ith row index
                                    // conditional on weights
                                    double w { (ptr_weights != nullptr) ? ptr_weights[row_idx] : 1.0 };
                                    if (ptr_actual[row_idx] == class_label)
                                        true_positive += w;
                                    else
                                        false_positive += w;
                                    ++j;
                                }

                                // 1.5.3) populate 
                                // the vectors and guard
                                // against zero-division
                                thresholds_vector[idx] = threshold_i;
                                recall_vector[idx] = (positives > 0) ? (true_positive / positives) : 0.0;
                                precision_vector[idx] = (true_positive + false_positive > 0) ? (true_positive / (true_positive + false_positive)) : 1.0;
                                label_vector[idx] = levels[c];
                                levels_vector[idx] = class_label;

                                // 1.5.4) increment
                                // row index
                                ++idx;
                            }
                            
                            // 1.6) add arbitrary threshold
                            // values at the end of the
                            // vectors
                            thresholds_vector[idx] = R_NegInf;
                            recall_vector[idx] = 1.0;
                            precision_vector[idx] = (true_positive + false_positive > 0) ? (true_positive / (true_positive + false_positive)) : 1.0;
                            label_vector[idx] = levels[c];
                            levels_vector[idx] = class_label;

                            // 1.6.1) increment to
                            // next row index
                            ++idx;
                        } else {
                            // without thresholds

                            // 1.5.1) iterate through response
                            // matrix
                            for (std::size_t i = 0; i <= n; ++i) {
                                // 1.5.1.1) initialize threshold
                                // vector with arbitrary threshold if
                                // at the start of the vector
                                // TODO: This can probably be done more elegantly. 
                                if (i == 0) {
                                    thresholds_vector[idx] = R_PosInf;
                                } else {

                                    // 1.5.1.1.1) extract
                                    // row index
                                    std::size_t row_idx { ptr_idx.get()[i - 1] };

                                    // 1.5.1.1.2) store corresponding
                                    // response value in the thresholds
                                    // vector
                                    thresholds_vector[idx] = response(row_idx, c);

                                    // 1.5.1.1.2) determine
                                    // the weight value (conditionally)
                                    // and increment accordingly
                                    double w { (ptr_weights != nullptr) ? ptr_weights[row_idx] : 1.0 };
                                    if (ptr_actual[row_idx] == class_label)
                                        true_positive += w;
                                    else
                                        false_positive += w;
                                }

                                // 1.5.1.2) calculate
                                // precision and recall
                                double precision { (true_positive + false_positive > 0) ? (true_positive / (true_positive + false_positive)) : 1.0 };
                                double recall { (positives > 0) ? (true_positive / positives) : 0.0 };
                                
                                // 1.5.1.3) populate
                                // vectors
                                precision_vector[idx] = precision;
                                recall_vector[idx] = recall;
                                label_vector[idx] = levels[c];
                                levels_vector[idx] = class_label;

                                // 1.5.1.3) increment
                                // to next row index
                                ++idx;
                            }
                        }
                    }

                    // 2) construct DataFrame
                    // NOTE: this is where
                    // most memory usage comes
                    // from
                    Rcpp::DataFrame output = Rcpp::DataFrame::create(
                        Rcpp::Named("threshold") = thresholds_vector,
                        Rcpp::Named("level") = levels_vector,
                        Rcpp::Named("label") = label_vector,
                        Rcpp::Named("recall") = recall_vector,
                        Rcpp::Named("precision") = precision_vector
                    );

                    // 2.1) add class prROC
                    // and data.frame class
                    // to the DataFrame
                    output.attr("class") = Rcpp::CharacterVector::create("prROC", "data.frame");

                    // 2.2) return the 
                    // DataFrame
                    return output;

            // end of function
            }


    private:
        /**
        * @brief Container for storing score information used in precision-recall computations.
        *
        * The structure holds a predicted score, a binary label, and a weight for an observation.
        * It is primarily used to aggregate data for computing micro-average precision by pairing
        * each score with its corresponding label and weight.
        *
        * @param score
        *  The predicted score for the observation.
        * @param label
        *  The binary label for the observation (1 for positive, 0 for negative).
        * @param weight
        *  The weight associated with the observation. Defaults to 1.0 if not specified.
        */
        struct threshold_container {
            double score;  /**< The predicted score for the observation. */
            int label;     /**< The binary label for the observation: 1 for positive, 0 for negative. */
            double weight; /**< The weight associated with the observation. */
        };
        
        /**
        * @brief Computes the average precision (AP) using an incremental area update.
        *
        * This function iteratively computes the average precision by aggregating the contributions
        * from each point in the precision-recall curve. It uses a sorted container of thresholds (and associated
        * binary labels and weights) to calculate cumulative true positives and false positives. At each step,
        * the recall and precision are updated, and the incremental area (using the provided integration function)
        * is added to the overall average precision.
        *
        * @param container A vector of threshold_container structures, each holding a thresholds, a binary label (1 for positive, 0 for negative),
        *                  and a corresponding weight. The container is expected to be sorted in descending order based on the thresholds.
        * @param positives The total weight of positive instances (true positives) used for normalizing the recall.
        * @param update_area A pointer to a function that calculates the area between two points on the precision-recall curve.
        *                    The function should take four parameters: the previous recall, previous precision, current recall,
        *                    and current precision, and return the incremental area as a double.
        *
        * @return The computed average precision as a double.
        */
        static double compute_average_precision(
            const std::vector<threshold_container>& container,
            double positives,
            double (*update_area)(double, double, double, double)) {

                // 0) declare variables
                // output variable
                double output { 0.0 };

                // true and false positive
                // variables
                double true_positive { 0.0 };
                double false_positive { 0.0 };

                // arbitrary precision and recall
                // values
                double previous_recall { 0.0 };
                double previous_precision { 0.0 };
                
                // 1) compute average
                // precision
                for (std::size_t i = 0; i < container.size(); i++) {

                    // 1.1) check if label is
                    // equal to 1
                    //
                    // NOTE: everything is binarized!
                    if (container[i].label == 1)
                        true_positive += container[i].weight;
                    else
                        false_positive += container[i].weight;

                    // 1.2) calculate precision
                    // and recall
                    double recall { true_positive / positives };
                    double precision { (true_positive + false_positive > 0) ? (true_positive / (true_positive + false_positive)) : 1.0 };

                    // 1.3) add to the total
                    // area
                    output += update_area(previous_recall, previous_precision, recall, precision);

                    // 1.4) store current
                    // precision and recall
                    // valuues for next iterative
                    // calculation
                    previous_recall = recall;
                    previous_precision = precision;
                }

                // 2) return output
                return output;
        }

        /**
        * @brief Computes the area of a trapezoid between two points on a curve.
        *
        * This function calculates the area under the curve between two consecutive points,
        * (x1, y1) and (x2, y2), using the trapezoidal rule. The area is computed as the product
        * of the width (difference in x-coordinates) and the average of the two y-values.
        *
        * @param x1 The x-coordinate of the first point.
        * @param y1 The y-coordinate of the first point.
        * @param x2 The x-coordinate of the second point.
        *
        * @param y2 The y-coordinate of the second point.
        * @return The area of the trapezoid.
        */        
        static inline double trapezoid_area(
            double x1, 
            double y1, 
            double x2, 
            double y2) {

                double width { (x2 - x1) };
                double height { 0.5 * (y1 + y2) };

                return width * height;
        }

        /**
        * @brief Computes the area under a curve using the step (non-interpolated) method.
        *
        * This function calculates the area under the curve between two consecutive points,
        * (x1, y1) and (x2, y2), using a step function approach. The area is computed by taking
        * the width (difference in x-coordinates) and multiplying it by the y-value at the second point.
        *
        * @param x1 The x-coordinate of the first point.
        * @param y1 The y-coordinate of the first point (unused in the area computation).
        * @param x2 The x-coordinate of the second point.
        * @param y2 The y-coordinate of the second point.
        *
        * @return The area computed using the step method.
        */
        static inline double step_area(
            double x1, 
            double y1, 
            double x2, 
            double y2) {

                double width { (x2 - x1) };

                return width * y2;
        }
        
        /**
        * @brief Prepares a sorted index array for a specified column in a numeric matrix.
        *
        * This function creates an array of indices corresponding to the rows of the provided
        * response matrix and sorts these indices in descending order based on the values
        * in the specified column. If the column is already presorted (i.e., in descending order),
        * the function skips the sorting step.
        *
        * @param response_matrix The numeric matrix containing predicted scores.
        * @param column The index of the column to process.
        * @param n The number of rows in the response matrix.
        * @param presorted A flag indicating whether the column is already sorted in descending order.
        *
        * @return A unique pointer to an array of sorted indices (of type std::size_t).
        */
        static inline std::unique_ptr<std::size_t[]> prepare_index(
            const Rcpp::NumericMatrix& response_matrix,
            std::size_t column,
            std::size_t n,
            bool presorted) {

                // 0) declare variables
                // smart pointer to indices
                std::unique_ptr<std::size_t[]> idx(new std::size_t[n]);

                // 1) populate indices
                // with starting from 0 to n
                std::iota(idx.get(), idx.get() + n, 0);

                // 2) sort idx by the j'th
                // column in the response matrix
                // if not presorted
                const double* matrix_vector { &response_matrix(0, column) };
                if (!presorted) {
                    std::sort(idx.get(), idx.get() + n, [matrix_vector](std::size_t a, std::size_t b) {
                        return matrix_vector[a] > matrix_vector[b];
                    });
                }

                // 3) return values
                return idx;
        }
        
        /**
        * @brief Counts the total positive weight for a given class.
        *
        * This function iterates over a sorted index array to compute the cumulative weight
        * of all instances that belong to the specified class. For each index, if the actual
        * class label matches the target class label, the corresponding weight (if provided)
        * or a default weight of 1.0 is added to the total. This is used to normalize the recall
        * values in precision-recall curve calculations.
        *
        * @param ptr_actual Pointer to an array of actual class labels.
        * @param ptr_weights Pointer to an array of observation weights (can be nullptr if weights are not provided).
        * @param idx A pointer to the sorted index array.
        * @param n The number of elements (rows) to process.
        * @param class_label The target class label for which to sum positive weights.
        *
        * @return The total positive weight (or count if unweighted) for the specified class.
        */
        static inline double count_positives(
            const int* ptr_actual,
            const double* ptr_weights,
            const std::size_t* idx,
            std::size_t n,
            std::size_t class_label) {

                // 0) declare values
                double positives { 0.0 };
                
                // 1) count number of positives
                for (std::size_t i = 0; i < n; i++) {
                    if (ptr_actual[idx[i]] == class_label)
                        positives += (ptr_weights != nullptr) ? ptr_weights[idx[i]] : 1.0;
                }
                
                // 2) return values
                return positives;
        }

        // delete class
        // to avoid mischiefs 
        // from compiler
        prROC()  = delete;
        ~prROC() = delete;
};

#endif
