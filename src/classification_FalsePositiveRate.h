#ifndef CLASSIFICATION_FPR_H
#define CLASSIFICATION_FPR_H

#include "classification_Helpers.h"
#include <RcppEigen.h>
#include <cmath>
#define EIGEN_USE_MKL_ALL
EIGEN_MAKE_ALIGNED_OPERATOR_NEW

class FalsePositiveRateMetric : public classification {
public:

    // Compute FPR with micro or macro aggregation
    Rcpp::NumericVector compute(const Eigen::MatrixXd& matrix, bool micro, bool na_rm) const override {
        Eigen::ArrayXd output(1);
        Eigen::ArrayXd fp(matrix.rows()), tn(matrix.rows()), auxillary(matrix.rows());

        FP(matrix, fp);
        TN(matrix, tn);

        if (micro) {
            double fp_sum = fp.sum(), tn_sum = tn.sum();
            output = Eigen::ArrayXd::Constant(1, fp_sum / (fp_sum + tn_sum));
        } else {
            auxillary = fp / (fp + tn);
            output = Eigen::ArrayXd::Constant(1, auxillary.sum() / auxillary.size());
        }

        return Rcpp::wrap(output);
    }

    // Compute FPR without micro aggregation
    Rcpp::NumericVector compute(const Eigen::MatrixXd& matrix, bool na_rm) const override {
        Eigen::ArrayXd output(matrix.rows());
        Eigen::ArrayXd fp(matrix.rows()), tn(matrix.rows());

        FP(matrix, fp);
        TN(matrix, tn);

        output = fp / (fp + tn);
        return Rcpp::wrap(output);
    }
};

#endif // CLASSIFICATION_FPR_H
