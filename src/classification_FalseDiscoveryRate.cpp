// [[Rcpp::depends(RcppEigen)]]
#include <RcppEigen.h>
#include "classification_FalseDiscoveryRate.h"

using namespace Rcpp;

//' @rdname fdr
//' @method fdr factor
//' @export
// [[Rcpp::export(fdr.factor)]]
Rcpp::NumericVector FalseDiscoveryRate(const Rcpp::IntegerVector& actual, const Rcpp::IntegerVector& predicted, Rcpp::Nullable<bool> micro = R_NilValue, const bool& na_rm = true) 
{
    FalseDiscoveryRateClass cook(na_rm);
    return recipe(cook, actual, predicted, std::nullopt, micro);
}

//' @rdname fdr
//' @method weighted.fdr factor
//' @export
// [[Rcpp::export(weighted.fdr.factor)]]
Rcpp::NumericVector weighted_FalseDiscoveryRate(const Rcpp::IntegerVector& actual, const Rcpp::IntegerVector& predicted, const Rcpp::NumericVector& w, Rcpp::Nullable<bool> micro = R_NilValue, const bool& na_rm = true) 
{
    FalseDiscoveryRateClass cook(na_rm);
    return recipe(cook, actual, predicted, w, micro);
}

//' @rdname fdr
//' @method fdr cmatrix
//' @export
// [[Rcpp::export(fdr.cmatrix)]]
Rcpp::NumericVector cmatrix_FalseDiscoveryRate(const Rcpp::NumericMatrix& x, Rcpp::Nullable<bool> micro = R_NilValue, const bool& na_rm = true) 
{
    FalseDiscoveryRateClass cook(na_rm);
    return recipe(cook, x, micro);
}
