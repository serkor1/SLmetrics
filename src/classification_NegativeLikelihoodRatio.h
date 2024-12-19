#ifndef CLASSIFICATION_NLR_H
#define CLASSIFICATION_NLR_H

#include "classification_Helpers.h"
#include <RcppEigen.h>
#include <cmath>
#define EIGEN_USE_MKL_ALL
EIGEN_MAKE_ALIGNED_OPERATOR_NEW

class NLRMetric : public classification {
public:

    // Compute NLR without micro aggregation
    Rcpp::NumericVector compute(const Eigen::MatrixXd& matrix) const override {
        Eigen::ArrayXd output(matrix.rows());
        Eigen::ArrayXd tp(matrix.rows()), fn(matrix.rows()), tn(matrix.rows()), fp(matrix.rows());
        Eigen::ArrayXd fnr(matrix.rows()), tnr(matrix.rows());

        TP(matrix, tp);
        FN(matrix, fn);
        TN(matrix, tn);
        FP(matrix, fp);

        fnr = fn / (tp + fn);
        tnr = tn / (fp + tn);

        output = fnr / tnr;

        return Rcpp::wrap(output);
    }

};

#endif // CLASSIFICATION_NLR_H