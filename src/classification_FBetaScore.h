#ifndef CLASSIFICATION_FBETASCORE_H
#define CLASSIFICATION_FBETASCORE_H

#include "classification_Helpers.h"
#include <RcppEigen.h>
#include <cmath>
#define EIGEN_USE_MKL_ALL
EIGEN_MAKE_ALIGNED_OPERATOR_NEW

class FBetaMetric : public classification {
public:

    Rcpp::NumericVector compute(const Eigen::MatrixXd& matrix, bool micro, double beta) const override {
        Eigen::ArrayXd output(1);
        Eigen::ArrayXd tp(matrix.rows()), fp(matrix.rows()), fn(matrix.rows());
        double beta_sq = beta * beta;

        TP(matrix, tp);
        FP(matrix, fp);
        FN(matrix, fn);

        if (micro) {

            double tp_sum = tp.sum(), fp_sum = fp.sum(), fn_sum = fn.sum();
            double precision = tp_sum / (tp_sum + fp_sum);
            double recall = tp_sum / (tp_sum + fn_sum);

            output = Eigen::ArrayXd::Constant(1, (precision + recall == 0)
                ? R_NaReal
                : (1 + beta_sq) * precision * recall / (beta_sq * precision + recall));
            
            return Rcpp::wrap(output);

        } else {
            Eigen::ArrayXd precision = tp / (tp + fp);
            Eigen::ArrayXd recall = tp / (tp + fn);

            output = (1 + beta_sq) * (precision * recall) / (beta_sq * precision + recall);

            return Rcpp::wrap(Eigen::ArrayXd::Constant(1, output.sum() / output.size()));
        }

        
    }

    Rcpp::NumericVector compute(const Eigen::MatrixXd& matrix, double beta) const override {
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
