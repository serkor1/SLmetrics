#ifndef CLASSIFICATION_ZEROONELOSS_H
#define CLASSIFICATION_ZEROONELOSS_H

#include "classification_Helpers.h"
#include <RcppEigen.h>
#define EIGEN_USE_MKL_ALL
EIGEN_MAKE_ALIGNED_OPERATOR_NEW

/*
    Simplified ZeroOneLoss class:
    Calculates ZeroOneLoss as (tp + tn) / N.
*/
class ZeroOneLossMetric : public classification {
public:
    // Compute overall accuracy
    Rcpp::NumericVector compute(const Eigen::MatrixXd& matrix, bool na_rm) const override {

        // 0) set sizes
        // of arrays
        Eigen::ArrayXd output(1);
        Eigen::ArrayXd tp(matrix.rows());

        // 1) extract values
        TP(matrix, tp);
        double N = matrix.sum();

        // 1) calculate 
        // Calculate total instances (N), TP, and TN
        // double total = matrix.sum(); // Total entries in the confusion matrix
        // double tp = matrix.diagonal().sum(); // Sum of the diagonal (True Positives)
        output = Eigen::ArrayXd::Constant(1, (N == 0) ? R_NaReal : (N - tp.sum()) / N);

        return Rcpp::wrap(output); // Wrap into NumericVector
    }

    // Dummy micro aggregation to adhere to base class
    Rcpp::NumericVector compute(const Eigen::MatrixXd& matrix, bool na_rm, bool micro) const override {
        return compute(matrix, na_rm); // Reuse the same function
    }
};

#endif