// [[Rcpp::depends(RcppEigen)]]
#include <RcppEigen.h>
#include "classification_FalseOmissionRate.h"

using namespace Rcpp;

//' @rdname fer
//' @method fer factor
//' @export
// [[Rcpp::export(fer.factor)]]
Rcpp::NumericVector FalseOmissionRate(const Rcpp::IntegerVector& actual, const Rcpp::IntegerVector& predicted, Rcpp::Nullable<bool> micro = R_NilValue, const bool& na_rm = true) 
{
    FalseOmissionRateClass cook(na_rm);
    return recipe(cook, actual, predicted, std::nullopt, micro);
}

//' @rdname fer
//' @method weighted.fer factor
//' @export
// [[Rcpp::export(weighted.fer.factor)]]
Rcpp::NumericVector weighted_FalseOmissionRate(const Rcpp::IntegerVector& actual, const Rcpp::IntegerVector& predicted, const Rcpp::NumericVector& w, Rcpp::Nullable<bool> micro = R_NilValue, const bool& na_rm = true) 
{
    FalseOmissionRateClass cook(na_rm);
    return recipe(cook, actual, predicted, w, micro);
}

//' @rdname fer
//' @method fer cmatrix
//' @export
// [[Rcpp::export(fer.cmatrix)]]
Rcpp::NumericVector cmatrix_FalseOmissionRate(const Rcpp::NumericMatrix& x, Rcpp::Nullable<bool> micro = R_NilValue, const bool& na_rm = true) 
{
    FalseOmissionRateClass cook(na_rm);
    return recipe(cook, x, micro);
}
