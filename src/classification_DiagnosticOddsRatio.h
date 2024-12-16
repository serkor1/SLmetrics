#ifndef CLASSIFICATION_DOR_H
#define CLASSIFICATION_DOR_H

#include "classification_Helpers.h"
#include <RcppEigen.h>
#include <cmath>
#define EIGEN_USE_MKL_ALL
EIGEN_MAKE_ALIGNED_OPERATOR_NEW

class DORMetric : public classification {
public:

    // Compute DOR with micro or macro aggregation
    Rcpp::NumericVector compute(const Eigen::MatrixXd& matrix, bool micro, bool na_rm) const override {
        Eigen::ArrayXd output(1), tp_sum(1), fn_sum(1), tn_sum(1), fp_sum(1);
        Eigen::ArrayXd tp(matrix.rows()), fn(matrix.rows()), tn(matrix.rows()), fp(matrix.rows()), auxillary(matrix.rows());

        TP(matrix, tp);
        FN(matrix, fn);
        TN(matrix, tn);
        FP(matrix, fp);

        if (micro) {

            tp_sum = tp.sum();
            fn_sum = fn.sum();
            tn_sum = tn.sum();
            fp_sum = fp.sum();
            
            output = (tp_sum * tn_sum) / (fp_sum * fn_sum);

        } else {            

            auxillary = (tp * tn) / (fp * fn);
            output = auxillary.sum() / auxillary.size();

        }

        return Rcpp::wrap(output);
    }

    // Compute DOR without micro aggregation
    Rcpp::NumericVector compute(const Eigen::MatrixXd& matrix, bool na_rm) const override {
        Eigen::ArrayXd output(matrix.rows());
        Eigen::ArrayXd tp(matrix.rows()), fn(matrix.rows()), tn(matrix.rows()), fp(matrix.rows());

        TP(matrix, tp);
        FN(matrix, fn);
        TN(matrix, tn);
        FP(matrix, fp);

        output = (tp * tn) / (fp * fn);
        return Rcpp::wrap(output);
    }
};

#endif // CLASSIFICATION_DOR_H