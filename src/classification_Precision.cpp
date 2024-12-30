// [[Rcpp::depends(RcppEigen)]]
#include <RcppEigen.h>
#include "classification_Precision.h" // PrecisionMetric definition

// Namespace for cleaner usage
using namespace Rcpp;

//' @rdname precision
//' @method precision factor
//' @export
// [[Rcpp::export(precision.factor)]]
Rcpp::NumericVector Precision(const Rcpp::IntegerVector& actual, const Rcpp::IntegerVector& predicted, Rcpp::Nullable<bool> micro = R_NilValue, bool na_rm = true) 
{
    PrecisionClass cook(na_rm);
    return recipe(cook, actual, predicted, std::nullopt, micro);
}

//' @rdname precision
//' @method weighted.precision factor
//' @export
// [[Rcpp::export(weighted.precision.factor)]]
Rcpp::NumericVector weighted_Precision(const Rcpp::IntegerVector& actual, const Rcpp::IntegerVector& predicted, const Rcpp::NumericVector& w, Rcpp::Nullable<bool> micro = R_NilValue, bool na_rm = true) 
{
    PrecisionClass cook(na_rm);
    return recipe(cook, actual, predicted, w, micro);
}

//' @rdname precision
//' @method precision cmatrix
//' @export
// [[Rcpp::export(precision.cmatrix)]]
Rcpp::NumericVector cmatrix_Precision(const NumericMatrix& x, Rcpp::Nullable<bool> micro = R_NilValue, const bool& na_rm = true) 
{
    PrecisionClass cook(na_rm);
    return recipe(cook, x, micro);
}

//' @rdname precision
//' @method ppv factor
//' @export
// [[Rcpp::export(ppv.factor)]]
Rcpp::NumericVector PositivePredictiveValue(const Rcpp::IntegerVector& actual, const Rcpp::IntegerVector& predicted, Rcpp::Nullable<bool> micro = R_NilValue, bool na_rm = true) 
{
    PrecisionClass cook(na_rm);
    return recipe(cook, actual, predicted, std::nullopt, micro);
}

//' @rdname precision
//' @method weighted.ppv factor
//' @export
// [[Rcpp::export(weighted.ppv.factor)]]
Rcpp::NumericVector weighted_PositivePredictiveValue(const Rcpp::IntegerVector& actual, const Rcpp::IntegerVector& predicted, const Rcpp::NumericVector& w, Rcpp::Nullable<bool> micro = R_NilValue, bool na_rm = true) 
{
    PrecisionClass cook(na_rm);
    return recipe(cook, actual, predicted, w, micro);
}

//' @rdname precision
//' @method ppv cmatrix
//' @export
// [[Rcpp::export(ppv.cmatrix)]]
Rcpp::NumericVector cmatrix_PositivePredictiveValue(const Rcpp::NumericMatrix& x, Rcpp::Nullable<bool> micro = R_NilValue, const bool& na_rm = true) 
{
    PrecisionClass cook(na_rm);
    return recipe(cook, x, micro);
}
