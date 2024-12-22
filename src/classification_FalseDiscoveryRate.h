#ifndef CLASSIFICATION_FDR_H
#define CLASSIFICATION_FDR_H

#include "classification_Helpers.h"
#include <RcppEigen.h>
#include <cmath>
#define EIGEN_USE_MKL_ALL
EIGEN_MAKE_ALIGNED_OPERATOR_NEW

class FalseDiscoveryRateMetric : public classification {
public:

    Rcpp::NumericVector compute(const Eigen::MatrixXd& matrix, bool do_micro, bool na_rm) const override {

        // 0) Declare variables and size
        // for efficiency.
        // NOTE: Micro and macro already wraps and exports as Rcpp
        Rcpp::NumericVector output(1);
        Eigen::ArrayXd fp(matrix.rows()), tp(matrix.rows());

        FP(matrix, fp);
        TP(matrix, tp);

        return do_micro
            ? micro(fp, fp + tp, na_rm)
            : macro(fp, fp + tp, na_rm);

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
