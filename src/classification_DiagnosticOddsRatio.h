#ifndef CLASSIFICATION_DOR_H
#define CLASSIFICATION_DOR_H

#include "classification_Helpers.h"
#include <RcppEigen.h>
#include <cmath>
#define EIGEN_USE_MKL_ALL
EIGEN_MAKE_ALIGNED_OPERATOR_NEW

class DiagnosticOddsRatioClass : public classification {

    public:

        Rcpp::NumericVector compute(const Eigen::MatrixXd& matrix) const override {
            Rcpp::NumericVector output {};
            Eigen::ArrayXd tp { matrix.rows() }, fn { matrix.rows() }, tn { matrix.rows() }, fp { matrix.rows() };

            TP(matrix, tp);
            FN(matrix, fn);
            TN(matrix, tn);
            FP(matrix, fp);

            output = (tp.sum() * tn.sum()) / (fp.sum() * fn.sum());
            
            return output;
        }
};

#endif // CLASSIFICATION_DOR_H