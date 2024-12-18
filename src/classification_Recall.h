#ifndef CLASSIFICATION_RECALL_H
#define CLASSIFICATION_RECALL_H

#include "classification_Utils.h" 
#include "classification_Helpers.h"
#include <RcppEigen.h>
#include <cmath>
#define EIGEN_USE_MKL_ALL
EIGEN_MAKE_ALIGNED_OPERATOR_NEW

/*
    NOTE:
        To increase maintainability all functions are passed through
        the confusion matrix. So there is no need to add a overloaded function
        for the weighted metrics.
*/
class RecallMetric : public classification {
public:

    // Compute recall with micro or macro aggregation
    Rcpp::NumericVector compute(const Eigen::MatrixXd& matrix, bool na_rm, bool micro) const override {
        
        // 0) declare the
        // output value and 
        // TP/FP
        Eigen::ArrayXd output(1);
        Eigen::ArrayXd tp(matrix.rows()), fn(matrix.rows());

        // 1) create TP and FP arrays
        // for calculations
        TP(matrix, tp);
        FN(matrix, fn); 

        // 2) conditional
        // computing of metric
        if (micro) {

            double tp_sum = tp.sum(), fn_sum = fn.sum();
            output = Eigen::ArrayXd::Constant(1, (tp_sum + fn_sum == 0) ? R_NaReal : tp_sum / (tp_sum + fn_sum));

        } else {

            
            output = tp / (tp + fn);

            if (na_rm) {
                double valid_sum = (output.isFinite().select(output, 0.0)).sum();
                double valid_count = output.isFinite().count();
                output = Eigen::ArrayXd::Constant(1, valid_count > 0 ? valid_sum / valid_count : R_NaReal);
            }

        }

        // 3) rerturn with 
        // wrap (R compatible classes)        
        return Rcpp::wrap(output);
    }

    // Compute recall without micro aggregation
    Rcpp::NumericVector compute(const Eigen::MatrixXd& matrix, bool na_rm) const override {
        
        // 0) declare the
        // output value and 
        // TP/FP
        Eigen::ArrayXd output(matrix.rows());
        Eigen::ArrayXd tp(matrix.rows()), fn(matrix.rows());

        // 1) create TP and FP arrays
        // for calculations
        TP(matrix, tp);
        FN(matrix, fn); 

        // 2) calculate metric
        output = tp / (tp + fn);

        // 3) rerturn with 
        // wrap (R compatible classes)   
        return Rcpp::wrap(output);
    }
};

#endif // CLASSIFICATION_RECALL_H
