// [[Rcpp::depends(RcppEigen)]]
#include <RcppEigen.h>
#include "classification_FalseDiscoveryRate.h"

using namespace Rcpp;

//' @rdname fdr
//' @method fdr factor
//' @export
// [[Rcpp::export(fdr.factor)]]
NumericVector fdr(const IntegerVector& actual, const IntegerVector& predicted, Nullable<bool> micro = R_NilValue, const bool& na_rm = true) {
    FalseDiscoveryRateMetric foo; // Instantiate FDR metric
    return classification_base(actual, predicted, foo, micro, na_rm);
}

//' @rdname fdr
//' @method weighted.fdr factor
//' @export
// [[Rcpp::export(weighted.fdr.factor)]]
NumericVector weighted_fdr(const IntegerVector& actual, const IntegerVector& predicted, const NumericVector& w, Nullable<bool> micro = R_NilValue, const bool& na_rm = true) {
    FalseDiscoveryRateMetric foo; // Instantiate FDR metric
    return classification_base(actual, predicted, w, foo, micro, na_rm);
}

//' @rdname fdr
//' @method fdr cmatrix
//' @export
// [[Rcpp::export(fdr.cmatrix)]]
NumericVector fdr_cmatrix(const IntegerMatrix& x, Nullable<bool> micro = R_NilValue, const bool& na_rm = true) {
    FalseDiscoveryRateMetric foo; // Instantiate FDR metric
    return classification_base(x, foo, micro, na_rm);
}
