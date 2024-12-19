#ifndef CLASSIFICATION_SPECIFICITY_H
#define CLASSIFICATION_SPECIFICITY_H

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
class SpecificityMetric : public classification {
public:

    // Compute specificity with micro or macro aggregation
    Rcpp::NumericVector compute(const Eigen::MatrixXd& matrix, bool do_micro, bool na_rm) const override {

        // 0) Declare variables and size
        // for efficiency.
        // NOTE: Micro and macro already wraps and exports as Rcpp
        Rcpp::NumericVector output(1);
        Eigen::ArrayXd tn(matrix.rows()), fp(matrix.rows());

        TN(matrix, tn);
        FP(matrix, fp);

        return do_micro
            ?  micro(tn, tn + fp, na_rm)
            :  macro(tn, tn + fp, na_rm);

    }

    // Compute specificity without micro aggregation
    Rcpp::NumericVector compute(const Eigen::MatrixXd& matrix, bool na_rm) const override {

        // 0) Declare output value and TN/FP arrays
        Eigen::ArrayXd output(matrix.rows());
        Eigen::ArrayXd tn(matrix.rows()), fp(matrix.rows());

        // 1) Create TN and FP arrays
        TN(matrix, tn);
        FP(matrix, fp);

        // 2) Calculate metric
        output = tn / (tn + fp);

        // 3) Return wrapped (R-compatible classes)
        return Rcpp::wrap(output);
    }
};

#endif // CLASSIFICATION_SPECIFICITY_H
