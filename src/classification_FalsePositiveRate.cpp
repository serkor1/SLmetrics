// [[Rcpp::depends(RcppEigen)]]
#include <RcppEigen.h>
#include "classification_FalsePositiveRate.h"

using namespace Rcpp;

//' @rdname fpr
//' @method fpr factor
//' @export
// [[Rcpp::export(fpr.factor)]]
NumericVector fpr(const IntegerVector& actual, const IntegerVector& predicted, Nullable<bool> micro = R_NilValue, const bool& na_rm = true) {
    FalsePositiveRateMetric foo; // Instantiate FPR metric
    return classification_base(actual, predicted, foo, micro, na_rm);
}

//' @rdname fpr
//' @method weighted.fpr.factor
//' @export
// [[Rcpp::export(weighted.fpr.factor)]]
NumericVector weighted_fpr(const IntegerVector& actual, const IntegerVector& predicted, const NumericVector& w, Nullable<bool> micro = R_NilValue, const bool& na_rm = true) {
    FalsePositiveRateMetric foo; // Instantiate FPR metric
    return classification_base(actual, predicted, w, foo, micro, na_rm);
}

//' @rdname fpr
//' @method fpr cmatrix
//' @export
// [[Rcpp::export(fpr.cmatrix)]]
NumericVector fpr_cmatrix(const IntegerMatrix& x, Nullable<bool> micro = R_NilValue, const bool& na_rm = true) {
    FalsePositiveRateMetric foo; // Instantiate FPR metric
    return classification_base(x, foo, micro, na_rm);
}
