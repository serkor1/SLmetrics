#ifndef CLASSIFICATION_PLR_H
#define CLASSIFICATION_PLR_H

#include "classification_Helpers.h"
#include <RcppEigen.h>
#include <cmath>
#define EIGEN_USE_MKL_ALL
EIGEN_MAKE_ALIGNED_OPERATOR_NEW

class PositiveLikelihoodRatioClass : public classification {

    public:

        Rcpp::NumericVector compute(const Eigen::MatrixXd& matrix) const override {
            Eigen::ArrayXd output(matrix.rows());
            Eigen::ArrayXd tp(matrix.rows()), fn(matrix.rows()), tn(matrix.rows()), fp(matrix.rows());
            Eigen::ArrayXd tpr(matrix.rows()), fpr(matrix.rows());

            TP(matrix, tp);
            FN(matrix, fn);
            TN(matrix, tn);
            FP(matrix, fp);

            tpr = tp / (tp + fn);
            fpr = fp / (fp + tn);

            output = tpr / fpr;

            return Rcpp::wrap(output);
        }
    
};

#endif // CLASSIFICATION_PLR_H