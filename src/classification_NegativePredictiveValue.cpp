// [[Rcpp::depends(RcppEigen)]]
#include <RcppEigen.h>
#include "classification_NegativePredictiveValue.h"

using namespace Rcpp;

//' @rdname npv
//' @method npv factor
//' @export
// [[Rcpp::export(npv.factor)]]
NumericVector npv(const IntegerVector& actual, const IntegerVector& predicted, Nullable<bool> micro = R_NilValue, const bool& na_rm = true) {
    NegativePredictiveValueMetric foo; // Instantiate NPV metric
    return classification_base(actual, predicted, foo, micro, na_rm);
}

//' @rdname npv
//' @method weighted.npv.factor
//' @export
// [[Rcpp::export(weighted.npv.factor)]]
NumericVector weighted_npv(const IntegerVector& actual, const IntegerVector& predicted, const NumericVector& w, Nullable<bool> micro = R_NilValue, const bool& na_rm = true) {
    NegativePredictiveValueMetric foo; // Instantiate NPV metric
    return classification_base(actual, predicted, w, foo, micro, na_rm);
}

//' @rdname npv
//' @method npv cmatrix
//' @export
// [[Rcpp::export(npv.cmatrix)]]
NumericVector npv_cmatrix(const IntegerMatrix& x, Nullable<bool> micro = R_NilValue, const bool& na_rm = true) {
    NegativePredictiveValueMetric foo; // Instantiate NPV metric
    return classification_base(x, foo, micro, na_rm);
}
