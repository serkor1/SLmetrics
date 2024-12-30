// [[Rcpp::depends(RcppEigen)]]
#include <RcppEigen.h>
#include "classification_NegativeLikelihoodRatio.h" // NegativeLikelihoodRatio definition

using namespace Rcpp;

//' @rdname nlr
//' @method nlr factor
//' @export
// [[Rcpp::export(nlr.factor)]]
Rcpp::NumericVector NegativeLikelihoodRatio(const Rcpp::IntegerVector& actual, const Rcpp::IntegerVector& predicted) 
{
    NegativeLikelihoodRatioClass cook;
    return recipe(cook, actual, predicted);
}

//' @rdname nlr
//' @method weighted.nlr factor
//' @export
// [[Rcpp::export(weighted.nlr.factor)]]
Rcpp::NumericVector weighted_NegativeLikelihoodRatio(const Rcpp::IntegerVector& actual, const Rcpp::IntegerVector& predicted, const Rcpp::NumericVector& w) 
{
    NegativeLikelihoodRatioClass cook;
    return recipe(cook, actual, predicted, w);
}

//' @rdname nlr
//' @method nlr cmatrix
//' @export
// [[Rcpp::export(nlr.cmatrix)]]
Rcpp::NumericVector cmatrix_NegativeLikelihoodRatio(const Rcpp::NumericMatrix& x) 
{
    NegativeLikelihoodRatioClass cook;
    return recipe(cook, x);
}
