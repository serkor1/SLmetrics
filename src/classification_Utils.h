#ifndef classification_Helpers_H
#define classification_Helpers_H

#include <Rcpp.h>
#include <Eigen/Dense>

/*
    Define two classes:
        1. Labels (Comparing IntegerVectors with IntegerVectorrs)
        2. Response (Comparing IntegerVectors with NumericVectors)
*/


class classification {
public:

    virtual Rcpp::NumericVector compute(const Eigen::MatrixXd& matrix, bool na_rm, bool micro) const = 0;


    virtual Rcpp::NumericVector compute(const Eigen::MatrixXd& matrix, bool na_rm) const = 0;


    virtual ~classification() = default;
};

#endif // classification_Helpers_H