#ifndef CLASSIFICATION_FPR_H
#define CLASSIFICATION_FPR_H

#include "classification_Helpers.h"
#include <RcppEigen.h>
#include <cmath>
#define EIGEN_USE_MKL_ALL
EIGEN_MAKE_ALIGNED_OPERATOR_NEW

class FalsePositiveRateClass : public classification {
    
    private:
        bool na_rm;

    public:
        FalsePositiveRateClass(bool na_rm) 
            : na_rm(na_rm) {}

        Rcpp::NumericVector compute(const Eigen::MatrixXd& matrix, bool do_micro) const override {
            
            // 0) Declare variables and size
            // for efficiency.
            // NOTE: Micro and macro already wraps and exports as Rcpp
            Rcpp::NumericVector output(1);
            Eigen::ArrayXd fp(matrix.rows()), tn(matrix.rows()), auxillary(matrix.rows());

            FP(matrix, fp);
            TN(matrix, tn);

            return do_micro
                ? micro(fp, fp + tn, na_rm)
                : macro(fp, fp + tn, na_rm);

        }

        Rcpp::NumericVector compute(const Eigen::MatrixXd& matrix) const override {
            Eigen::ArrayXd output(matrix.rows());
            Eigen::ArrayXd fp(matrix.rows()), tn(matrix.rows());

            FP(matrix, fp);
            TN(matrix, tn);

            output = fp / (fp + tn);
            return Rcpp::wrap(output);
        }
};

#endif
