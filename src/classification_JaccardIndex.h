#ifndef CLASSIFICATION_JACCARD_H
#define CLASSIFICATION_JACCARD_H

#include "classification_Helpers.h"
#include <RcppEigen.h>
#include <cmath>
#define EIGEN_USE_MKL_ALL
EIGEN_MAKE_ALIGNED_OPERATOR_NEW

class JaccardIndexMetric : public classification {
public:

    Rcpp::NumericVector compute(const Eigen::MatrixXd& matrix, bool do_micro, bool na_rm) const override {
        Eigen::ArrayXd output(1);
        Eigen::ArrayXd tp(matrix.rows()), fp(matrix.rows()), fn(matrix.rows());

        TP(matrix, tp);
        FP(matrix, fp);
        FN(matrix, fn);


        // 2) retun with 
        // ternary expression
        return do_micro
            ? micro(tp, (tp + fp + fn), na_rm)
            : macro(tp, (tp + fp + fn), na_rm);

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
