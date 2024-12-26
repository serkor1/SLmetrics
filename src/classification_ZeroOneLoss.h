#ifndef CLASSIFICATION_ZEROONELOSS_H
#define CLASSIFICATION_ZEROONELOSS_H

#include "classification_Helpers.h"
#include <RcppEigen.h>
#define EIGEN_USE_MKL_ALL
EIGEN_MAKE_ALIGNED_OPERATOR_NEW

class ZeroOneLossClass : public classification {

    public:
        
        Rcpp::NumericVector compute(const Eigen::MatrixXd& matrix) const override {

            // 0) set sizes
            // of arrays
            Eigen::ArrayXd output(1);
            Eigen::ArrayXd tp(matrix.rows());

            // 1) extract values
            TP(matrix, tp);
            double N = matrix.sum();

            // 2) calculate
            // output
            output = Eigen::ArrayXd::Constant(1, (N == 0) ? R_NaReal : (N - tp.sum()) / N);

            return Rcpp::wrap(output); // Wrap into NumericVector
        }
    
};

#endif