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
class FalseOmissionRateClass : public classification {

    private:
        bool na_rm;

    public:

        FalseOmissionRateClass(bool na_rm)
            : na_rm(na_rm) {}

        Rcpp::NumericVector compute(const Eigen::MatrixXd& matrix, bool do_micro) const override {
            // 0) Declare variables and size
            // for efficiency.
            // NOTE: Micro and macro already wraps and exports as Rcpp
            Rcpp::NumericVector output(1);
            Eigen::ArrayXd fn(matrix.rows()), tn(matrix.rows());

            // Create FN and TN arrays for calculations
            FN(matrix, fn);
            TN(matrix, tn);

            return do_micro
                ? micro(fn, fn + tn, na_rm)
                : macro(fn, fn + tn, na_rm);
            
        }

        Rcpp::NumericVector compute(const Eigen::MatrixXd& matrix) const override {
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

#endif
