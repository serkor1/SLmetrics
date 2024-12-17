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
class NegativePredictiveValueMetric : public classification {
public:

    // Compute NPV with micro or macro aggregation
    Rcpp::NumericVector compute(const Eigen::MatrixXd& matrix, bool na_rm, bool micro) const override {
        // Declare the output value and TN/FN arrays
        Eigen::ArrayXd output(1);
        Eigen::ArrayXd tn(matrix.rows()), fn(matrix.rows());

        // Populate TN and FN arrays for calculations
        TN(matrix, tn);
        FN(matrix, fn);

        // Conditional computation of metric
        if (micro) {
            double tn_sum = tn.sum(), fn_sum = fn.sum();
            output = Eigen::ArrayXd::Constant(1, (tn_sum + fn_sum == 0) ? R_NaReal : tn_sum / (tn_sum + fn_sum));
        } else {
            output = tn / (tn + fn);

            if (na_rm) {
                double valid_sum = (output.isFinite().select(output, 0.0)).sum();
                double valid_count = output.isFinite().count();
                output = Eigen::ArrayXd::Constant(1, valid_count > 0 ? valid_sum / valid_count : R_NaReal);
            }
        }

        // Return with R-compatible class
        return Rcpp::wrap(output);
    }

    // Compute NPV without micro aggregation
    Rcpp::NumericVector compute(const Eigen::MatrixXd& matrix, bool na_rm) const override {
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
