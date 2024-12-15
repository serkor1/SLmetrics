#ifndef CLASSIFICATION_FMI_H
#define CLASSIFICATION_FMI_H

#include "classification_Helpers.h"
#include <RcppEigen.h>
#define EIGEN_USE_MKL_ALL
EIGEN_MAKE_ALIGNED_OPERATOR_NEW


/*
* Calculation of the Fawlks Mallows
* Index follows that of https://en.wikipedia.org/wiki/Fowlkes%E2%80%93Mallows_index
* for any specific value k.
*
* Using the sqrt(PPV * TPR)-approach directly yields
* a different result than scikit-learn.Hence this approach
* is prefferred
*/
class FMIMetric : public classification {
public:

  Rcpp::NumericVector compute(const Eigen::MatrixXd& matrix) const override {

    // 0) set sizes
    // of arrays
    Eigen::ArrayXd output(1), N(1), row_sum(matrix.rows()), col_sum(matrix.cols()), pk(1), qk(1), tk(1);

    // 1) calculate values
    // accordingly
    N       = matrix.sum();
    row_sum = matrix.rowwise().sum();
    col_sum = matrix.colwise().sum();
    tk      = matrix.cwiseProduct(matrix).sum();
    pk      = row_sum.matrix().squaredNorm() - N;
    qk      = row_sum.matrix().squaredNorm() - N;

    // 2) calculate output
    // value
    output  = (tk.square()) / (pk.square());

    return Rcpp::wrap(output.array().sqrt());

  }


};

#endif