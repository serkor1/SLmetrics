#ifndef CLASSIFICATION_FBETASCORE_H
#define CLASSIFICATION_FBETASCORE_H

#include "classification_Helpers.h"
#include <RcppEigen.h>
#include <cmath>
#define EIGEN_USE_MKL_ALL
EIGEN_MAKE_ALIGNED_OPERATOR_NEW

class FBetaScoreClass : public classification {

    private:
        double beta;
        bool na_rm;

    public:

        FBetaScoreClass(double beta, bool na_rm)
            : beta(beta), na_rm(na_rm) {}

        Rcpp::NumericVector compute(const Eigen::MatrixXd& matrix, bool do_micro) const override {
            
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
            Eigen::ArrayXd precision = do_micro
                ? micro<Eigen::ArrayXd>(tp, (tp + fp), na_rm)
                : macro<Eigen::ArrayXd>(tp, (tp + fp), na_rm);

            Eigen::ArrayXd recall = do_micro
                ? micro<Eigen::ArrayXd>(tp, (tp + fn), na_rm)
                : macro<Eigen::ArrayXd>(tp, (tp + fn), na_rm);


            // 2) retun with 
            // ternary expression
            return do_micro
                ? micro((1.0 + beta_sq) * tp, (1.0 + beta_sq) * tp + beta_sq * fn + fp, na_rm)
                : macro((1.0 + beta_sq) * tp, (1.0 + beta_sq) * tp + beta_sq * fn + fp, na_rm);


        }

        Rcpp::NumericVector compute(const Eigen::MatrixXd& matrix) const override {
            Eigen::ArrayXd output(matrix.rows());
            Eigen::ArrayXd tp(matrix.rows()), fp(matrix.rows()), fn(matrix.rows());
            double beta_sq = beta * beta;

            TP(matrix, tp);
            FP(matrix, fp);
            FN(matrix, fn);

            Eigen::ArrayXd precision = tp / (tp + fp);
            Eigen::ArrayXd recall    = tp / (tp + fn);

            output = (1.0 + beta_sq) * (precision * recall) / (beta_sq * precision + recall);
            return Rcpp::wrap(output);
        }
};

#endif
