#ifndef CLASSIFICATION_MCC_H
#define CLASSIFICATION_MCC_H

#include "classification_Helpers.h"
#include <RcppEigen.h>
#define EIGEN_USE_MKL_ALL
EIGEN_MAKE_ALIGNED_OPERATOR_NEW

/*
    MCCMetric class:
    Calculates the Matthews Correlation Coefficient (MCC) using the provided
    confusion matrix or actual/predicted labels.
*/
class MatthewsCorrelationCoefficientClass : public classification {

    public:
        
        Rcpp::NumericVector compute(const Eigen::MatrixXd& matrix) const override {

            Eigen::ArrayXd output(1), N(1), row_sum(matrix.rows()), col_sum(matrix.cols()), tp_sum(1), cov_ytyp(1), cov_ypyp(1), cov_ytyt(1), product(1);

            
            // 1) calculate values
            // accordingly
            tp_sum  = matrix.diagonal().sum();
            row_sum = matrix.rowwise().sum();
            col_sum = matrix.colwise().sum();
            N       = matrix.sum();

            // 2) calculate covariances
            cov_ytyp = tp_sum * N - row_sum.matrix().dot(col_sum.matrix());
            cov_ypyp = N * N - col_sum.matrix().squaredNorm();
            cov_ytyt = N * N - row_sum.matrix().squaredNorm();

            // 3) calcualte the product
            product = cov_ypyp * cov_ytyt;

            // 4) calculate output
            // value
            output  = cov_ytyp / product.array().sqrt();

            return Rcpp::wrap(output);
        }

};

#endif
