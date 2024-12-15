#ifndef CLASSIFICATION_PLR_H
#define CLASSIFICATION_PLR_H

#include "classification_Helpers.h"
#include <RcppEigen.h>
#include <cmath>
#define EIGEN_USE_MKL_ALL
EIGEN_MAKE_ALIGNED_OPERATOR_NEW

class PLRMetric : public classification {
public:

    // Compute PLR with micro or macro aggregation
    Rcpp::NumericVector compute(const Eigen::MatrixXd& matrix, bool na_rm, bool micro) const override {
        Eigen::ArrayXd output(1);
        Eigen::ArrayXd tp(matrix.rows()), fn(matrix.rows()), tn(matrix.rows()), fp(matrix.rows());

        TP(matrix, tp);
        FN(matrix, fn);
        TN(matrix, tn);
        FP(matrix, fp);

        if (micro) {
            double tp_sum = tp.sum(), fn_sum = fn.sum(), tn_sum = tn.sum(), fp_sum = fp.sum();
            output = Eigen::ArrayXd::Constant(1, (tp_sum + fn_sum == 0 || tn_sum + fp_sum == 0)
                ? R_NaReal
                : (tp_sum / (tp_sum + fn_sum)) / (1.0 - (tn_sum / (tn_sum + fp_sum))));
        } else {
            output = (tp / (tp + fn)) / (1.0 - (tn / (tn + fp)));
            if (na_rm) {
                double valid_sum = (output.isFinite().select(output, 0.0)).sum();
                double valid_count = output.isFinite().count();
                output = Eigen::ArrayXd::Constant(1, valid_count > 0 ? valid_sum / valid_count : R_NaReal);
            }
        }

        return Rcpp::wrap(output);
    }

    // Compute PLR without micro aggregation
    Rcpp::NumericVector compute(const Eigen::MatrixXd& matrix, bool na_rm) const override {
        Eigen::ArrayXd output(matrix.rows());
        Eigen::ArrayXd tp(matrix.rows()), fn(matrix.rows()), tn(matrix.rows()), fp(matrix.rows());

        TP(matrix, tp);
        FN(matrix, fn);
        TN(matrix, tn);
        FP(matrix, fp);

        output = (tp / (tp + fn)) / (1.0 - (tn / (tn + fp)));
        return Rcpp::wrap(output);
    }
};

#endif // CLASSIFICATION_PLR_H
