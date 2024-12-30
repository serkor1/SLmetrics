#ifndef CLASSIFICATION_BALANCED_ACCURACY_H
#define CLASSIFICATION_BALANCED_ACCURACY_H

#include "classification_Helpers.h"
#include <RcppEigen.h>
#include <cmath>
#define EIGEN_USE_MKL_ALL
EIGEN_MAKE_ALIGNED_OPERATOR_NEW

class BalancedAccuracyClass : public classification {

private:
    bool adjust;
    bool na_rm;

public:
    // Constructor
    BalancedAccuracyClass(bool adjust, bool na_rm)
        : adjust(adjust), na_rm(na_rm) {}

    Rcpp::NumericVector compute(const Eigen::MatrixXd& matrix) const override {
        // 0) define values
        Eigen::ArrayXd output(1);                       
        Eigen::ArrayXd tp(matrix.rows()); 
        Eigen::ArrayXd temp(matrix.rows());
        double n_classes;

        // 1) calculate True
        // positives
        TP(matrix, tp);

        // 2) calculate class
        // wise values
        temp = tp / matrix.rowwise().sum().array();

        // 2.1) determine
        // denominator
        n_classes = na_rm
                ? (temp.isNaN() == false).count()
                : temp.size();

        // 3) adjust for
        // chance findings
        if (adjust)
        {
            temp -= 1.0 / n_classes;
            temp /= (1.0 - (1.0 / n_classes));
        }

        // 4) calculate
        // value        
        output = na_rm
            ? Eigen::ArrayXd::Constant(1, temp.isNaN().select(0, temp).sum() / n_classes)
            : Eigen::ArrayXd::Constant(1, temp.isNaN().select(0, temp).sum() / n_classes);

        // 5) return
        // with wrap
        return Rcpp::wrap(output);

    };

};

#endif
