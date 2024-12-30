// [[Rcpp::depends(RcppEigen)]]
#include <RcppEigen.h>
#include "classification_DiagnosticOddsRatio.h" // DiagnosticOddsRatioClass definition

using namespace Rcpp;

//' @rdname dor
//' @method dor factor
//' @export
// [[Rcpp::export(dor.factor)]]
Rcpp::NumericVector DiagnosticOddsRatio(const Rcpp::IntegerVector& actual, const Rcpp::IntegerVector& predicted) 
{
    DiagnosticOddsRatioClass cook;
    return recipe(cook, actual, predicted);
}

//' @rdname dor
//' @method weighted.dor factor
//' @export
// [[Rcpp::export(weighted.dor.factor)]]
Rcpp::NumericVector weighted_DiagnosticOddsRatio(const Rcpp::IntegerVector& actual, const Rcpp::IntegerVector& predicted, const Rcpp::NumericVector& w) 
{
    DiagnosticOddsRatioClass cook;
    return recipe(cook, actual, predicted, w);
}

//' @rdname dor
//' @method dor cmatrix
//' @export
// [[Rcpp::export(dor.cmatrix)]]
Rcpp::NumericVector cmatrix_DiagnosticOddsRatio(const Rcpp::NumericMatrix& x) 
{
    DiagnosticOddsRatioClass cook;
    return recipe(cook, x);
}
