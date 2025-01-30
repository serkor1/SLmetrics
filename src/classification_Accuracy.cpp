// [[Rcpp::depends(RcppEigen)]]
#include <RcppEigen.h>
#include "classification_Accuracy.h"

using namespace Rcpp;

//' @rdname accuracy
//' @method accuracy factor
//' @export
// [[Rcpp::export(accuracy.factor)]]
Rcpp::NumericVector Accuracy(const IntegerVector& actual, const Rcpp::IntegerVector& predicted) 
{
    AccuracyClass cook;
    return recipe(cook, actual, predicted);
}

//' @rdname accuracy
//' @method weighted.accuracy factor
//' @export
// [[Rcpp::export(weighted.accuracy.factor)]]
Rcpp::NumericVector weighted_Accuracy(const IntegerVector& actual, const Rcpp::IntegerVector& predicted, const Rcpp::NumericVector& w) 
{
    AccuracyClass cook;
    return recipe(cook, actual, predicted, w);
}

//' @rdname accuracy
//' @method accuracy cmatrix
//' @export
// [[Rcpp::export(accuracy.cmatrix)]]
Rcpp::NumericVector cmatrix_Accuracy(const Rcpp::NumericMatrix& x) 
{
    AccuracyClass cook;
    return recipe(cook, x);
}
