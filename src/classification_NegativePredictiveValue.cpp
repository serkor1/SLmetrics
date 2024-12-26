// [[Rcpp::depends(RcppEigen)]]
#include <RcppEigen.h>
#include "classification_NegativePredictiveValue.h"

using namespace Rcpp;

//' @rdname npv
//' @method npv factor
//' @export
// [[Rcpp::export(npv.factor)]]
Rcpp::NumericVector NegativePredictitveValue(const Rcpp::IntegerVector& actual, const Rcpp::IntegerVector& predicted, Rcpp::Nullable<bool> micro = R_NilValue, const bool& na_rm = true) 
{
    NegativePredictiveValueClass cook(na_rm);
    return recipe(cook, actual, predicted, std::nullopt, micro);
}

//' @rdname npv
//' @method weighted.npv factor
//' @export
// [[Rcpp::export(weighted.npv.factor)]]
Rcpp::NumericVector weighted_NegativePredictitveValue(const Rcpp::IntegerVector& actual, const Rcpp::IntegerVector& predicted, const Rcpp::NumericVector& w, Rcpp::Nullable<bool> micro = R_NilValue, const bool& na_rm = true) 
{
    NegativePredictiveValueClass cook(na_rm);
    return recipe(cook, actual, predicted, w, micro);
}

//' @rdname npv
//' @method npv cmatrix
//' @export
// [[Rcpp::export(npv.cmatrix)]]
Rcpp::NumericVector cmatrix_NegativePredictitveValue(const Rcpp::NumericMatrix& x, Rcpp::Nullable<bool> micro = R_NilValue, const bool& na_rm = true) 
{
    NegativePredictiveValueClass cook(na_rm);
    return recipe(cook, x, micro);
}
