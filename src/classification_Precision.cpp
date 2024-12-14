// [[Rcpp::depends(RcppEigen)]]
#include <RcppEigen.h>
#include "classification_Precision.h" // PrecisionMetric definition

// Namespace for cleaner usage
using namespace Rcpp;

//' @rdname precision
//' @method precision factor
//' @export
// [[Rcpp::export(precision.factor)]]
Rcpp::NumericVector precision(const Rcpp::IntegerVector& actual, const Rcpp::IntegerVector& predicted, Rcpp::Nullable<bool> micro = R_NilValue, bool na_rm = true) {
    PrecisionMetric foo; // Instantiate PrecisionMetric
    return classification_base(actual, predicted, foo, micro, na_rm);
}

//' @rdname precision
//' @method precision factor
//' @export
// [[Rcpp::export(weighted.precision.factor)]]
Rcpp::NumericVector weighted_precision(const Rcpp::IntegerVector& actual, const Rcpp::IntegerVector& predicted, const Rcpp::NumericVector& w, Rcpp::Nullable<bool> micro = R_NilValue, bool na_rm = true) {
    PrecisionMetric foo; // Instantiate PrecisionMetric
    return classification_base(actual, predicted, w, foo, micro, na_rm);
}

//' @rdname precision
//' @method precision cmatrix
//' @export
// [[Rcpp::export(precision.cmatrix)]]
Rcpp::NumericVector precision_cmatrix(const IntegerMatrix& x, Rcpp::Nullable<bool> micro = R_NilValue, const bool& na_rm = true) {
    PrecisionMetric foo; // Instantiate PrecisionMetric
    return classification_base(x, foo, micro, na_rm);
}

//' @rdname precision
//' @method ppv factor
//' @export
// [[Rcpp::export(ppv.factor)]]
Rcpp::NumericVector ppv(const Rcpp::IntegerVector& actual, const Rcpp::IntegerVector& predicted, Rcpp::Nullable<bool> micro = R_NilValue, bool na_rm = true) {
    PrecisionMetric foo; // Instantiate PrecisionMetric
    return classification_base(actual, predicted, foo, micro, na_rm);
}

//' @rdname precision
//' @method ppv factor
//' @export
// [[Rcpp::export(weighted.ppv.factor)]]
Rcpp::NumericVector weighted_ppv(const Rcpp::IntegerVector& actual, const Rcpp::IntegerVector& predicted, const Rcpp::NumericVector& w, Rcpp::Nullable<bool> micro = R_NilValue, bool na_rm = true) {
    PrecisionMetric foo; // Instantiate PrecisionMetric
    return classification_base(actual, predicted, w, foo, micro, na_rm);
}

//' @rdname precision
//' @method ppv cmatrix
//' @export
// [[Rcpp::export(ppv.cmatrix)]]
Rcpp::NumericVector ppv_cmatrix(const IntegerMatrix& x, Rcpp::Nullable<bool> micro = R_NilValue, const bool& na_rm = true) {
    PrecisionMetric foo; // Instantiate PrecisionMetric
    return classification_base(x, foo, micro, na_rm);
}
