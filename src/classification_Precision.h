#ifndef CLASSIFICATION_PRECISION_H
#define CLASSIFICATION_PRECISION_H

#include "classification_Helpers.h"
#include <RcppEigen.h>
#include <cmath>
#define EIGEN_USE_MKL_ALL
EIGEN_MAKE_ALIGNED_OPERATOR_NEW

/*
    NOTE:
        To increase maintainability, all functions are passed through
        the confusion matrix. So there is no need to add an overloaded function
        for the weighted metrics.
*/
class PrecisionClass : public classification {

    private:
        bool na_rm;
        
    public:
        PrecisionClass(bool na_rm)
            : na_rm(na_rm) {}

        Rcpp::NumericVector compute(const Eigen::MatrixXd& matrix, bool do_micro) const override {
            
            // 0) Declare variables and size
            // for efficiency.
            // NOTE: Micro and macro already wraps and exports as Rcpp
            Rcpp::NumericVector output(1);
            Eigen::ArrayXd tp(matrix.rows()), fp(matrix.rows());

            // 1) create TP and FP arrays
            // for calculations
            TP(matrix, tp);
            FP(matrix, fp);

            return do_micro
                ? micro(tp, tp + fp, na_rm)
                : macro(tp, tp + fp, na_rm);

        }

        Rcpp::NumericVector compute(const Eigen::MatrixXd& matrix) const override {
            
            // 0) declare the
            // output value and 
            // TP/FP
            Eigen::ArrayXd output(matrix.rows());
            Eigen::ArrayXd tp(matrix.rows()), fp(matrix.rows());

            // 1) create TP and FP arrays
            // for calculations
            TP(matrix, tp);
            FP(matrix, fp);

            // 2) calculate metric
            output = tp / (tp + fp);

            // 3) return with 
            // wrap (R compatible classes)   
            return Rcpp::wrap(output);
        }
};

#endif // CLASSIFICATION_PRECISION_H
