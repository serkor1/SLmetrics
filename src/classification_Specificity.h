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
    Rcpp::NumericVector compute(const Eigen::MatrixXd& matrix, bool micro, bool na_rm) const override {

        // 0) Declare output value and TN/FP arrays
        Eigen::ArrayXd output(1), tn_sum(1), fp_sum(1);
        Eigen::ArrayXd tn(matrix.rows()), fp(matrix.rows()), auxillary(matrix.rows());

        // 1) Create TN and FP arrays
        TN(matrix, tn);
        FP(matrix, fp);

        // 2) Conditional computation of metric
        if (micro) {

            // 2.1) calculate sums
            tn_sum = Eigen::ArrayXd::Constant(1, tn.sum()); fp_sum = Eigen::ArrayXd::Constant(1, fp.sum());

            // 2.2) calculate output
            output = tn_sum / (tn_sum + fp_sum);

        } else {

            // 2.1) calculate intermediate
            // value
            auxillary = tn / (tn + fp);

            // 2.2) calculate output
            output = auxillary.sum() / auxillary.size();

        }

        // 3) Return wrapped (R-compatible classes)
        return Rcpp::wrap(output);
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
