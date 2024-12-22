// [[Rcpp::depends(RcppEigen)]]
#include <RcppEigen.h>
#include "classification_PositiveLikelihoodRatio.h" // PLRMetric definition

using namespace Rcpp;

//' @rdname plr
//' @method plr factor
//' @export
// [[Rcpp::export(plr.factor)]]
NumericVector plr(const IntegerVector& actual, const IntegerVector& predicted, Nullable<bool> micro = R_NilValue) {
    PLRMetric foo; // Instantiate PLRMetric
    return classification_base(actual, predicted, foo, micro);
}

//' @rdname plr
//' @method weighted.plr factor
//' @export
// [[Rcpp::export(weighted.plr.factor)]]
NumericVector weighted_plr(const IntegerVector& actual, const IntegerVector& predicted, const NumericVector& w, Nullable<bool> micro = R_NilValue) {
    PLRMetric foo; // Instantiate PLRMetric
    return classification_base(actual, predicted, w, foo, micro);
}

//' @rdname plr
//' @method plr cmatrix
//' @export
// [[Rcpp::export(plr.cmatrix)]]
NumericVector plr_cmatrix(const NumericMatrix& x, Nullable<bool> micro = R_NilValue) {
    PLRMetric foo; // Instantiate PLRMetric
    return classification_base(x, foo, micro);
}
