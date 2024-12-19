#ifndef CLASSIFICATION_BALANCED_ACCURACY_H
#define CLASSIFICATION_BALANCED_ACCURACY_H

#include "classification_Helpers.h"
#include <RcppEigen.h>
#include <cmath>
#define EIGEN_USE_MKL_ALL
EIGEN_MAKE_ALIGNED_OPERATOR_NEW

/*
    BalancedAccuracyMetric class:
    Calculates the average recall across classes,
    with an optional adjustment for chance agreement.
*/

class BalancedAccuracyMetric : public classification {
public:

    Rcpp::NumericVector compute(const Eigen::MatrixXd& matrix, bool adjust) const override {
        // 0) define values
        Eigen::ArrayXd output(1);                       
        Eigen::ArrayXd tp(matrix.rows()); 
        Eigen::ArrayXd temp(matrix.rows());   

        // 1) calculate True
        // positives
        TP(matrix, tp);

        // 2) calculate class
        // wise values
        temp = tp / matrix.rowwise().sum().array();

        // 3) adjust for
        // chance findings
        if (adjust)
        {
            temp -= 1.0 / matrix.rows();
            temp /= 1.0 / matrix.rows();
        }

        // 4) calculate
        // value        
        output = Eigen::ArrayXd::Constant(1, temp.sum()/temp.size());

        // 5) return
        // with wrap
        return Rcpp::wrap(output);

    };

};

#endif // CLASSIFICATION_BALANCED_ACCURACY_H
