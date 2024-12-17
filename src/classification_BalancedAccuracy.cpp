// [[Rcpp::depends(RcppEigen)]]
#include <RcppEigen.h>
#include "classification_BalancedAccuracy.h"

using namespace Rcpp;

//' @rdname baccuracy
//' @method baccuracy factor
//' @export
// [[Rcpp::export(baccuracy.factor)]]
NumericVector baccuracy(const IntegerVector& actual, const IntegerVector& predicted, const bool& adjust = false, const bool& na_rm = true) {
    BalancedAccuracyMetric foo; // Instantiate BalancedAccuracyMetric
    return classification_base(actual, predicted, foo, na_rm, adjust);
}

//' @rdname baccuracy
//' @method weighted.baccuracy factor
//' @export
// [[Rcpp::export(weighted.baccuracy.factor)]]
NumericVector weighted_baccuracy(const IntegerVector& actual, const IntegerVector& predicted, const NumericVector& w,  const bool& adjust = false, const bool& na_rm = true) {
    BalancedAccuracyMetric foo; // Instantiate BalancedAccuracyMetric
    return classification_base(actual, predicted, w, foo, na_rm, adjust);
}

//' @rdname baccuracy
//' @method baccuracy cmatrix
//' @export
// [[Rcpp::export(baccuracy.cmatrix)]]
NumericVector baccuracy_cmatrix(const NumericMatrix& x, const bool& adjust = false, const bool& na_rm = true) {
    BalancedAccuracyMetric foo; // Instantiate BalancedAccuracyMetric
    return classification_base(x, foo, na_rm, adjust);
}
