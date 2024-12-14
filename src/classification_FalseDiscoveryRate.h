#ifndef CLASSIFICATION_FDR_H
#define CLASSIFICATION_FDR_H

#include "src_Helpers.h"
#include "classification_Utils.h"
#include "classification_Helpers.h"
#include <RcppEigen.h>
#include <cmath>
#define EIGEN_USE_MKL_ALL
EIGEN_MAKE_ALIGNED_OPERATOR_NEW

class FDRMetric : public classification {
public:

    Rcpp::NumericVector compute(const Eigen::MatrixXd& matrix, bool na_rm, bool micro) const override {
        Eigen::ArrayXd output(1);
        Eigen::ArrayXd fp(matrix.rows()), tp(matrix.rows());

        FP(matrix, fp);
        TP(matrix, tp);

        if (micro) {
            double fp_sum = fp.sum(), tp_sum = tp.sum();
            output = Eigen::ArrayXd::Constant(1, (fp_sum + tp_sum == 0)
                ? R_NaReal
                : fp_sum / (fp_sum + tp_sum));
        } else {
            output = fp / (fp + tp);
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
        Eigen::ArrayXd fp(matrix.rows()), tp(matrix.rows());

        FP(matrix, fp);
        TP(matrix, tp);

        output = fp / (fp + tp);
        return Rcpp::wrap(output);
    }
};

#endif // CLASSIFICATION_FDR_H
