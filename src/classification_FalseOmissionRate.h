#ifndef CLASSIFICATION_FALSE_OMISSION_RATE_H
#define CLASSIFICATION_FALSE_OMISSION_RATE_H

#include "classification_Helpers.h"
#include <RcppEigen.h>
#include <cmath>
#define EIGEN_USE_MKL_ALL
EIGEN_MAKE_ALIGNED_OPERATOR_NEW

/*
    NOTE:
        To increase maintainability all functions are passed through
        the confusion matrix. So there is no need to add an overloaded function
        for the weighted metrics.
*/
class FalseOmissionRateMetric : public classification {
public:

    // Compute FOR with micro or macro aggregation
    Rcpp::NumericVector compute(const Eigen::MatrixXd& matrix, bool na_rm, bool micro) const override {
        // Declare the output value and FN/TN arrays
        Eigen::ArrayXd output(1);
        Eigen::ArrayXd fn(matrix.rows()), tn(matrix.rows());

        // Create FN and TN arrays for calculations
        FN(matrix, fn);
        TN(matrix, tn);

        // Conditional computation of metric
        if (micro) {
            double fn_sum = fn.sum(), tn_sum = tn.sum();
            output = Eigen::ArrayXd::Constant(1, (fn_sum + tn_sum == 0) ? R_NaReal : fn_sum / (fn_sum + tn_sum));
        } else {
            output = fn / (fn + tn);

            if (na_rm) {
                double valid_sum = (output.isFinite().select(output, 0.0)).sum();
                double valid_count = output.isFinite().count();
                output = Eigen::ArrayXd::Constant(1, valid_count > 0 ? valid_sum / valid_count : R_NaReal);
            }
        }

        // Return with R-compatible class
        return Rcpp::wrap(output);
    }

    // Compute FOR without micro aggregation
    Rcpp::NumericVector compute(const Eigen::MatrixXd& matrix, bool na_rm) const override {
        // Declare the output value and FN/TN arrays
        Eigen::ArrayXd output(matrix.rows());
        Eigen::ArrayXd fn(matrix.rows()), tn(matrix.rows());

        // Create FN and TN arrays for calculations
        FN(matrix, fn);
        TN(matrix, tn);

        // Calculate metric
        output = fn / (fn + tn);

        // Return with R-compatible class
        return Rcpp::wrap(output);
    }
};

#endif // CLASSIFICATION_FALSE_OMISSION_RATE_H
