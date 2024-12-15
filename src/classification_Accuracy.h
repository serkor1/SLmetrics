#ifndef CLASSIFICATION_ACCURACY_H
#define CLASSIFICATION_ACCURACY_H

#include "classification_Helpers.h"
#include <RcppEigen.h>
#define EIGEN_USE_MKL_ALL
EIGEN_MAKE_ALIGNED_OPERATOR_NEW

/*
    Simplified AccuracyMetric class:
    Calculates accuracy as (tp + tn) / N.
*/
class AccuracyMetric : public classification {
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
        output = Eigen::ArrayXd::Constant(1, (N == 0) ? R_NaReal : tp.sum() / N);

        return Rcpp::wrap(output); // Wrap into NumericVector
    }
};

#endif // CLASSIFICATION_ACCURACY_H
