#ifndef CLASSIFICATION_SPECIFICITY_H
#define CLASSIFICATION_SPECIFICITY_H

#include "src_Helpers.h"
#include "classification_Utils.h"
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
    Rcpp::NumericVector compute(const Eigen::MatrixXd& matrix, bool na_rm, bool micro) const override {

        // 0) Declare output value and TN/FP arrays
        Eigen::ArrayXd output(1);
        Eigen::ArrayXd tn(matrix.rows()), fp(matrix.rows());

        // 1) Create TN and FP arrays
        TN(matrix, tn);
        FP(matrix, fp);

        // 2) Conditional computation of metric
        if (micro) {

            double tn_sum = tn.sum(), fp_sum = fp.sum();
            output = Eigen::ArrayXd::Constant(1, (tn_sum + fp_sum == 0) ? R_NaReal : tn_sum / (tn_sum + fp_sum));

        } else {

            output = tn / (tn + fp);

            if (na_rm) {
                double valid_sum = (output.isFinite().select(output, 0.0)).sum();
                double valid_count = output.isFinite().count();
                output = Eigen::ArrayXd::Constant(1, valid_count > 0 ? valid_sum / valid_count : R_NaReal);
            }

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
