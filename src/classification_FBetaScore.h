#ifndef CLASSIFICATION_FBETASCORE_H
#define CLASSIFICATION_FBETASCORE_H

#include "classification_Helpers.h"
#include <RcppEigen.h>
#include <cmath>
#define EIGEN_USE_MKL_ALL
EIGEN_MAKE_ALIGNED_OPERATOR_NEW

class FBetaMetric : public classification {
public:

    Rcpp::NumericVector compute(const Eigen::MatrixXd& matrix, double beta, bool do_micro, bool na_rm) const override {
        
        // 0) Declare variables and size
        // for efficiency.
        // NOTE: Micro and macro already wraps and exports as Rcpp
        Rcpp::NumericVector output(1);
        Eigen::ArrayXd tp(matrix.rows()), fp(matrix.rows()), fn(matrix.rows());
        double beta_sq = beta * beta;

        TP(matrix, tp);
        FP(matrix, fp);
        FN(matrix, fn);

        // 1) define recall 
        // and recall
        const Eigen::ArrayXd& precision = tp / (tp + fp);
        const Eigen::ArrayXd& recall    = tp / (tp + fn);

        // 2) retun with 
        // ternary expression
        return do_micro
            ? micro((1 + beta_sq) * (precision * recall), (beta_sq * precision + recall), na_rm)
            : macro((1 + beta_sq) * (precision * recall), (beta_sq * precision + recall), na_rm);

    }

    Rcpp::NumericVector compute(const Eigen::MatrixXd& matrix, double beta, bool na_rm) const override {
        Eigen::ArrayXd output(matrix.rows());
        Eigen::ArrayXd tp(matrix.rows()), fp(matrix.rows()), fn(matrix.rows());
        double beta_sq = beta * beta;

        TP(matrix, tp);
        FP(matrix, fp);
        FN(matrix, fn);

        Eigen::ArrayXd precision = tp / (tp + fp);
        Eigen::ArrayXd recall = tp / (tp + fn);

        output = (1 + beta_sq) * (precision * recall) / (beta_sq * precision + recall);
        return Rcpp::wrap(output);
    }
};

#endif // CLASSIFICATION_FBETASCORE_H
