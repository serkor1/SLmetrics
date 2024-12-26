#ifndef CLASSIFICATION_NEGATIVE_PREDICTIVE_VALUE_H
#define CLASSIFICATION_NEGATIVE_PREDICTIVE_VALUE_H

#include "classification_Helpers.h"
#include <RcppEigen.h>
#include <cmath>
#define EIGEN_USE_MKL_ALL
EIGEN_MAKE_ALIGNED_OPERATOR_NEW

/*
    NOTE:
        To increase maintainability, all functions are passed through
        the confusion matrix. So there is no need to add an overloaded function
        for the weighted metrics.
*/
class NegativePredictiveValueClass : public classification {

    private:
        bool na_rm;

    public:
 
        NegativePredictiveValueClass(bool na_rm)
            : na_rm(na_rm) {}

        // Compute NPV with micro or macro aggregation
        Rcpp::NumericVector compute(const Eigen::MatrixXd& matrix, bool do_micro) const override {
            // Declare the output value and TN/FN arrays
            Eigen::ArrayXd output(1);
            Eigen::ArrayXd tn(matrix.rows()), fn(matrix.rows());

            // Populate TN and FN arrays for calculations
            TN(matrix, tn);
            FN(matrix, fn);


            // 2) retun with 
            // ternary expression
            return do_micro
                ? micro(tn, (tn + fn), na_rm)
                : macro(tn, (tn + fn), na_rm);

        }

        // Compute NPV without micro aggregation
        Rcpp::NumericVector compute(const Eigen::MatrixXd& matrix) const override {
            // Declare the output value and TN/FN arrays
            Eigen::ArrayXd output(matrix.rows());
            Eigen::ArrayXd tn(matrix.rows()), fn(matrix.rows());

            // Populate TN and FN arrays for calculations
            TN(matrix, tn);
            FN(matrix, fn);

            // Calculate metric
            output = tn / (tn + fn);

            // Return with R-compatible class
            return Rcpp::wrap(output);
        }
};

#endif // CLASSIFICATION_NEGATIVE_PREDICTIVE_VALUE_H
