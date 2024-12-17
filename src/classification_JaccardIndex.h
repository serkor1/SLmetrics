#ifndef CLASSIFICATION_JACCARD_H
#define CLASSIFICATION_JACCARD_H

#include "classification_Helpers.h"
#include <RcppEigen.h>
#include <cmath>
#define EIGEN_USE_MKL_ALL
EIGEN_MAKE_ALIGNED_OPERATOR_NEW

class JaccardIndexMetric : public classification {
public:

    Rcpp::NumericVector compute(const Eigen::MatrixXd& matrix, bool na_rm, bool micro) const override {
        Eigen::ArrayXd output(1);
        Eigen::ArrayXd tp(matrix.rows()), fp(matrix.rows()), fn(matrix.rows());

        TP(matrix, tp);
        FP(matrix, fp);
        FN(matrix, fn);

        if (micro) {
            double tp_sum = tp.sum(), fp_sum = fp.sum(), fn_sum = fn.sum();
            output = Eigen::ArrayXd::Constant(1, (tp_sum + fp_sum + fn_sum == 0)
                ? R_NaReal
                : tp_sum / (tp_sum + fp_sum + fn_sum));
        } else {
            output = tp / (tp + fp + fn);
            if (na_rm) {
                double valid_sum = (output.isFinite().select(output, 0.0)).sum();
                double valid_count = output.isFinite().count();
                output = Eigen::ArrayXd::Constant(1, valid_count > 0 ? valid_sum / valid_count : R_NaReal);
            }
        }

        return Rcpp::wrap(output);
    }

    Rcpp::NumericVector compute(const Eigen::MatrixXd& matrix, bool na_rm) const override {
        Eigen::ArrayXd output(matrix.rows());
        Eigen::ArrayXd tp(matrix.rows()), fp(matrix.rows()), fn(matrix.rows());

        TP(matrix, tp);
        FP(matrix, fp);
        FN(matrix, fn);

        output = tp / (tp + fp + fn);
        return Rcpp::wrap(output);
    }
};

#endif // CLASSIFICATION_JACCARD_H
