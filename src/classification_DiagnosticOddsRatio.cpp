// [[Rcpp::depends(RcppEigen)]]
#include <RcppEigen.h>
#include "classification_DiagnosticOddsRatio.h" // DORMetric definition

using namespace Rcpp;

//' @rdname dor
//' @method dor factor
//' @export
// [[Rcpp::export(dor.factor)]]
NumericVector dor(const IntegerVector& actual, const IntegerVector& predicted, Nullable<bool> micro = R_NilValue) {
    DORMetric foo; // Instantiate DORMetric
    return classification_base(actual, predicted, foo, micro);
}

//' @rdname dor
//' @method weighted.dor factor
//' @export
// [[Rcpp::export(weighted.dor.factor)]]
NumericVector weighted_dor(const IntegerVector& actual, const IntegerVector& predicted, const NumericVector& w, Nullable<bool> micro = R_NilValue) {
    DORMetric foo; // Instantiate DORMetric
    return classification_base(actual, predicted, w, foo, micro);
}

//' @rdname dor
//' @method dor cmatrix
//' @export
// [[Rcpp::export(dor.cmatrix)]]
NumericVector dor_cmatrix(const NumericMatrix& x, Nullable<bool> micro = R_NilValue) {
    DORMetric foo; // Instantiate DORMetric
    return classification_base(x, foo, micro);
}
