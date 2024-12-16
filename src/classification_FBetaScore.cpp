// [[Rcpp::depends(RcppEigen)]]
#include <RcppEigen.h>
#include "classification_FBetaScore.h"

using namespace Rcpp;

//' @rdname fbeta
//' @method fbeta factor
//' @export
// [[Rcpp::export(fbeta.factor)]]
NumericVector fbeta(const IntegerVector& actual, const IntegerVector& predicted, const double& beta = 1.0, Nullable<bool> micro = R_NilValue) {
    FBetaMetric foo; // Instantiate F-Beta metric with the provided beta value
    return classification_base(actual, predicted, foo, micro, beta);
}

//' @rdname fbeta
//' @method weighted.fbeta factor
//' @export
// [[Rcpp::export(weighted.fbeta.factor)]]
NumericVector weighted_fbeta(const IntegerVector& actual, const IntegerVector& predicted, const NumericVector& w, const double& beta = 1.0, Nullable<bool> micro = R_NilValue) {
    FBetaMetric foo; // Instantiate F-Beta metric with the provided beta value
    return classification_base(actual, predicted, w, foo, micro, beta);
}

//' @rdname fbeta
//' @method fbeta cmatrix
//' @export
// [[Rcpp::export(fbeta.cmatrix)]]
NumericVector fbeta_cmatrix(const NumericMatrix& x, const double& beta = 1.0, Nullable<bool> micro = R_NilValue) {
    FBetaMetric foo; // Instantiate F-Beta metric with the provided beta value
    return classification_base(x, foo, micro, beta);
}
