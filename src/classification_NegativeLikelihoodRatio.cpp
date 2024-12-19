// [[Rcpp::depends(RcppEigen)]]
#include <RcppEigen.h>
#include "classification_NegativeLikelihoodRatio.h" // NLRMetric definition

using namespace Rcpp;

//' @rdname nlr
//' @method nlr factor
//' @export
// [[Rcpp::export(nlr.factor)]]
NumericVector nlr(const IntegerVector& actual, const IntegerVector& predicted, Nullable<bool> micro = R_NilValue) {
    NLRMetric foo; // Instantiate NLRMetric
    return classification_base(actual, predicted, foo, micro);
}

//' @rdname nlr
//' @method weighted.nlr factor
//' @export
// [[Rcpp::export(weighted.nlr.factor)]]
NumericVector weighted_nlr(const IntegerVector& actual, const IntegerVector& predicted, const NumericVector& w, Nullable<bool> micro = R_NilValue) {
    NLRMetric foo; // Instantiate NLRMetric
    return classification_base(actual, predicted, w, foo, micro);
}

//' @rdname nlr
//' @method nlr cmatrix
//' @export
// [[Rcpp::export(nlr.cmatrix)]]
NumericVector nlr_cmatrix(const NumericMatrix& x, Nullable<bool> micro = R_NilValue) {
    NLRMetric foo; // Instantiate NLRMetric
    return classification_base(x, foo, micro);
}
