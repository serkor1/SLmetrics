// [[Rcpp::depends(RcppEigen)]]
#include <RcppEigen.h>
#include "classification_PositiveLikelihoodRatio.h" // PLRMetric definition

using namespace Rcpp;

//' @rdname plr
//' @method plr factor
//' @export
// [[Rcpp::export(plr.factor)]]
Rcpp::NumericVector PositiveLikelihoodRatio(const Rcpp::IntegerVector& actual, const Rcpp::IntegerVector& predicted) 
{
    PositiveLikelihoodRatioClass cook;
    return recipe(cook, actual, predicted);
}

//' @rdname plr
//' @method weighted.plr factor
//' @export
// [[Rcpp::export(weighted.plr.factor)]]
Rcpp::NumericVector weighted_PositiveLikelihoodRatio(const Rcpp::IntegerVector& actual, const Rcpp::IntegerVector& predicted, const Rcpp::NumericVector& w) 
{
    PositiveLikelihoodRatioClass cook;
    return recipe(cook, actual, predicted, w);
}

//' @rdname plr
//' @method plr cmatrix
//' @export
// [[Rcpp::export(plr.cmatrix)]]
Rcpp::NumericVector cmatrix_PositiveLikelihoodRatio(const Rcpp::NumericMatrix& x) 
{
    PositiveLikelihoodRatioClass cook;
    return recipe(cook, x);
}
