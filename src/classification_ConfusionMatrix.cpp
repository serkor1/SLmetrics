// [[Rcpp::depends(RcppEigen)]]
#include <RcppEigen.h>
#include "classification_ConfusionMatrix.h"
#include <Rcpp.h>
using namespace Rcpp;

//' @rdname cmatrix
//' @method cmatrix factor
//' @export
// [[Rcpp::export(cmatrix.factor)]]
Rcpp::NumericMatrix UnweightedConfusionMatrix(const Rcpp::IntegerVector& actual, const Rcpp::IntegerVector& predicted) 
{
    ConfusionMatrixClass args(actual, predicted);
    return args.constructMatrix();
}

//' @rdname cmatrix
//' @method weighted.cmatrix factor
//' @export
// [[Rcpp::export(weighted.cmatrix.factor)]]
Rcpp::NumericMatrix WeightedConfusionMatrix(const Rcpp::IntegerVector& actual, const Rcpp::IntegerVector& predicted, const Rcpp::NumericVector& w) 
{
    ConfusionMatrixClass args(actual, predicted);
    return args.constructMatrix(w);
}
