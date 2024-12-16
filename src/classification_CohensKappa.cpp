// [[Rcpp::depends(RcppEigen)]]
#include <RcppEigen.h>
#include "classification_CohensKappa.h"

using namespace Rcpp;

//' @rdname ckappa
//' @method ckappa factor
//' @export
// [[Rcpp::export(ckappa.factor)]]
NumericVector ckappa(const IntegerVector& actual, const IntegerVector& predicted, const double& beta = 0.0) {
    CohensKappaMetric foo; // Instantiate CohensKappaMetric
    return classification_base(actual, predicted, foo, beta);
}

//' @rdname ckappa
//' @method weighted.ckappa factor
//' @export
// [[Rcpp::export(weighted.ckappa.factor)]]
NumericVector weighted_ckappa(const IntegerVector& actual, const IntegerVector& predicted, const NumericVector& w, const double& beta = 0.0) {
    CohensKappaMetric foo; // Instantiate CohensKappaMetric
    return classification_base(actual, predicted, w, foo, beta);
}

//' @rdname ckappa
//' @method ckappa cmatrix
//' @export
// [[Rcpp::export(ckappa.cmatrix)]]
NumericVector ckappa_cmatrix(const IntegerMatrix& x, const double& beta = 0.0) {
    CohensKappaMetric foo; // Instantiate CohensKappaMetric
    return classification_base(x, foo, beta);
}
