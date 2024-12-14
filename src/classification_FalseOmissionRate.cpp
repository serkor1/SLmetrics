// [[Rcpp::depends(RcppEigen)]]
#include <RcppEigen.h>
#include "classification_FalseOmissionRate.h"

using namespace Rcpp;

//' @rdname fer
//' @method fer factor
//' @export
// [[Rcpp::export(fer.factor)]]
NumericVector fer(const IntegerVector& actual, const IntegerVector& predicted, Nullable<bool> micro = R_NilValue, const bool& na_rm = true) {
    FalseOmissionRateMetric foo; // Instantiate FOR metric
    return classification_base(actual, predicted, foo, micro, na_rm);
}

//' @rdname fer
//' @method weighted.fer.factor
//' @export
// [[Rcpp::export(weighted.fer.factor)]]
NumericVector weighted_fer(const IntegerVector& actual, const IntegerVector& predicted, const NumericVector& w, Nullable<bool> micro = R_NilValue, const bool& na_rm = true) {
    FalseOmissionRateMetric foo; // Instantiate FOR metric
    return classification_base(actual, predicted, w, foo, micro, na_rm);
}

//' @rdname fer
//' @method fer cmatrix
//' @export
// [[Rcpp::export(fer.cmatrix)]]
NumericVector fer_cmatrix(const IntegerMatrix& x, Nullable<bool> micro = R_NilValue, const bool& na_rm = true) {
    FalseOmissionRateMetric foo; // Instantiate FOR metric
    return classification_base(x, foo, micro, na_rm);
}
