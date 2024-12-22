// [[Rcpp::depends(RcppEigen)]]
#include <RcppEigen.h>
#include "classification_ZeroOneLoss.h"
using namespace Rcpp;

//' @rdname zerooneloss
//' @method zerooneloss factor
//' @export
// [[Rcpp::export(zerooneloss.factor)]]
Rcpp::NumericVector zerooneloss(const Rcpp::IntegerVector& actual, const Rcpp::IntegerVector& predicted) {
    ZeroOneLossMetric foo; // Instantiate ZeroOneLossMetric
    return classification_base(actual, predicted, foo);
}

//' @rdname zerooneloss
//' @method weighted.zerooneloss factor
//' @export
// [[Rcpp::export(weighted.zerooneloss.factor)]]
Rcpp::NumericVector weighted_zerooneloss(const Rcpp::IntegerVector& actual, const Rcpp::IntegerVector& predicted, const NumericVector& w) {
    ZeroOneLossMetric foo; // Instantiate ZeroOneLossMetric
    return classification_base(actual, predicted, w, foo);
}

//' @rdname zerooneloss
//' @method zerooneloss cmatrix
//' @export
// [[Rcpp::export(zerooneloss.cmatrix)]]
Rcpp::NumericVector zerooneloss_cmatrix(const Rcpp::NumericMatrix& x) {
  ZeroOneLossMetric foo; // Instantiate ZeroOneLossMetric
  return classification_base(x, foo);
}
