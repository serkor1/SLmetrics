// [[Rcpp::depends(RcppEigen)]]
#include <RcppEigen.h>
#include "classification_NegativeLikelihoodRatio.h" // NLRMetric definition

using namespace Rcpp;

//' @rdname nlr
//' @method nlr factor
//' @export
// [[Rcpp::export(nlr.factor)]]
NumericVector nlr(const IntegerVector& actual, const IntegerVector& predicted, Nullable<bool> micro = R_NilValue, const bool& na_rm = true) {
    NLRMetric foo; // Instantiate NLRMetric
    return classification_base(actual, predicted, foo, micro, na_rm);
}

//' @rdname nlr
//' @method weighted.nlr factor
//' @export
// [[Rcpp::export(weighted.nlr.factor)]]
NumericVector weighted_nlr(const IntegerVector& actual, const IntegerVector& predicted, const NumericVector& w, Nullable<bool> micro = R_NilValue, const bool& na_rm = true) {
    NLRMetric foo; // Instantiate NLRMetric
    return classification_base(actual, predicted, w, foo, micro, na_rm);
}

//' @rdname nlr
//' @method nlr cmatrix
//' @export
// [[Rcpp::export(nlr.cmatrix)]]
NumericVector nlr_cmatrix(const IntegerMatrix& x, Nullable<bool> micro = R_NilValue, const bool& na_rm = true) {
    NLRMetric foo; // Instantiate NLRMetric
    return classification_base(x, foo, micro, na_rm);
}
