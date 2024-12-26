// [[Rcpp::depends(RcppEigen)]]
#include <RcppEigen.h>
#include "classification_FalsePositiveRate.h"

using namespace Rcpp;

//' @rdname fpr
//' @method fpr factor
//' @export
// [[Rcpp::export(fpr.factor)]]
Rcpp::NumericVector FalsePositiveRate(const Rcpp::IntegerVector& actual, const Rcpp::IntegerVector& predicted, Rcpp::Nullable<bool> micro = R_NilValue, const bool& na_rm = true) 
{
    FalsePositiveRateClass cook(na_rm);
    return recipe(cook, actual, predicted, std::nullopt, micro);
}

//' @rdname fpr
//' @method weighted.fpr factor
//' @export
// [[Rcpp::export(weighted.fpr.factor)]]
Rcpp::NumericVector weighted_FalsePositiveRate(const Rcpp::IntegerVector& actual, const Rcpp::IntegerVector& predicted, const Rcpp::NumericVector& w, Rcpp::Nullable<bool> micro = R_NilValue, const bool& na_rm = true) 
{
    FalsePositiveRateClass cook(na_rm);
    return recipe(cook, actual, predicted, w, micro);
}

//' @rdname fpr
//' @method fpr cmatrix
//' @export
// [[Rcpp::export(fpr.cmatrix)]]
Rcpp::NumericVector cmatrix_FalsePositiveRate(const Rcpp::NumericMatrix& x, Rcpp::Nullable<bool> micro = R_NilValue, const bool& na_rm = true) 
{
    FalsePositiveRateClass cook(na_rm);
    return recipe(cook, x, micro);
}

//' @rdname fpr
//' @method fallout factor
//' @export
// [[Rcpp::export(fallout.factor)]]
Rcpp::NumericVector Fallout(const Rcpp::IntegerVector& actual, const Rcpp::IntegerVector& predicted, Rcpp::Nullable<bool> micro = R_NilValue, const bool& na_rm = true) 
{
    FalsePositiveRateClass cook(na_rm);
    return recipe(cook, actual, predicted, std::nullopt, micro);
}

//' @rdname fpr
//' @method weighted.fallout factor
//' @export
// [[Rcpp::export(weighted.fallout.factor)]]
Rcpp::NumericVector weighted_Fallout(const Rcpp::IntegerVector& actual, const Rcpp::IntegerVector& predicted, const Rcpp::NumericVector& w, Rcpp::Nullable<bool> micro = R_NilValue, const bool& na_rm = true) 
{
    FalsePositiveRateClass cook(na_rm);
    return recipe(cook, actual, predicted, w, micro);
}

//' @rdname fpr
//' @method fallout cmatrix
//' @export
// [[Rcpp::export(fallout.cmatrix)]]
Rcpp::NumericVector cmatrix_Fallout(const Rcpp::NumericMatrix& x, Rcpp::Nullable<bool> micro = R_NilValue, const bool& na_rm = true) 
{
    FalsePositiveRateClass cook(na_rm);
    return recipe(cook, x, micro);
}
