// [[Rcpp::depends(RcppEigen)]]
#include <RcppEigen.h>
#include "classification_Accuracy.h"

using namespace Rcpp;

//' @rdname accuracy
//' @method accuracy factor
//' @export
// [[Rcpp::export(accuracy.factor)]]
NumericVector accuracy(const IntegerVector& actual, const IntegerVector& predicted) {
    AccuracyMetric foo; // Instantiate AccuracyMetric
    return classification_base(actual, predicted, foo);
}

//' @rdname accuracy
//' @method weighted.accuracy factor
//' @export
// [[Rcpp::export(weighted.accuracy.factor)]]
NumericVector weighted_accuracy(const IntegerVector& actual, const IntegerVector& predicted, const NumericVector& w) {
    AccuracyMetric foo; // Instantiate AccuracyMetric
    return classification_base(actual, predicted, w, foo);
}

//' @rdname accuracy
//' @method accuracy cmatrix
//' @export
// [[Rcpp::export(accuracy.cmatrix)]]
NumericVector accuracy_cmatrix(const NumericMatrix& x) {
    AccuracyMetric foo; // Instantiate AccuracyMetric
    return classification_base(x, foo);
}
