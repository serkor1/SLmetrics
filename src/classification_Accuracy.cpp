// [[Rcpp::depends(RcppEigen)]]
#include <RcppEigen.h>
#include "classification_Accuracy.h"

using namespace Rcpp;

//' @rdname accuracy
//' @method accuracy factor
//' @export
// [[Rcpp::export(accuracy.factor)]]
NumericVector accuracy(const IntegerVector& actual, const IntegerVector& predicted, const bool& na_rm = true) {
    AccuracyMetric foo; // Instantiate AccuracyMetric
    return classification_base(actual, predicted, foo, na_rm);
}

//' @rdname accuracy
//' @method weighted.accuracy.factor
//' @export
// [[Rcpp::export(weighted.accuracy.factor)]]
NumericVector weighted_accuracy(const IntegerVector& actual, const IntegerVector& predicted, const NumericVector& w, const bool& na_rm = true) {
    AccuracyMetric foo; // Instantiate AccuracyMetric
    return classification_base(actual, predicted, w, foo, na_rm);
}

//' @rdname accuracy
//' @method accuracy cmatrix
//' @export
// [[Rcpp::export(accuracy.cmatrix)]]
NumericVector accuracy_cmatrix(const IntegerMatrix& x, const bool& na_rm = true) {
    AccuracyMetric foo; // Instantiate AccuracyMetric
    return classification_base(x, foo, na_rm);
}
