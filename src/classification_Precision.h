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
class PrecisionMetric : public classification {
public:

    // Compute precision with micro or macro aggregation
    Rcpp::NumericVector compute(const Eigen::MatrixXd& matrix, bool na_rm, bool micro) const override {
        
        // 0) declare the
        // output value and 
        // TP/FP
        Eigen::ArrayXd output(1);
        Eigen::ArrayXd tp(matrix.rows()), fp(matrix.rows());

        // 1) create TP and FP arrays
        // for calculations
        TP(matrix, tp);
        FP(matrix, fp);

        // 2) conditional
        // computing of metric
        if (micro) {

            double tp_sum = tp.sum(), fp_sum = fp.sum();
            output = Eigen::ArrayXd::Constant(1, (tp_sum + fp_sum == 0) ? R_NaReal : tp_sum / (tp_sum + fp_sum));

        } else {

            output = tp / (tp + fp);

            if (na_rm) {
                double valid_sum = (output.isFinite().select(output, 0.0)).sum();
                double valid_count = output.isFinite().count();
                output = Eigen::ArrayXd::Constant(1, valid_count > 0 ? valid_sum / valid_count : R_NaReal);
            }

        }

        // 3) return with 
        // wrap (R compatible classes)        
        return Rcpp::wrap(output);
    }

    // Compute precision without micro aggregation
    Rcpp::NumericVector compute(const Eigen::MatrixXd& matrix, bool na_rm) const override {
        
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
