// [[Rcpp::depends(RcppEigen)]]
#include <RcppEigen.h>
#include "classification_JaccardIndex.h"

using namespace Rcpp;

//' @rdname jaccard
//' @method jaccard factor
//' @export
// [[Rcpp::export(jaccard.factor)]]
NumericVector jaccard(const IntegerVector& actual, const IntegerVector& predicted, Nullable<bool> micro = R_NilValue, const bool& na_rm = true) {
    JaccardIndexMetric foo; // Instantiate Jaccard Index metric
    return classification_base(actual, predicted, foo, micro, na_rm);
}

//' @rdname jaccard
//' @method weighted.jaccard.factor
//' @export
// [[Rcpp::export(weighted.jaccard.factor)]]
NumericVector weighted_jaccard(const IntegerVector& actual, const IntegerVector& predicted, const NumericVector& w, Nullable<bool> micro = R_NilValue, const bool& na_rm = true) {
    JaccardIndexMetric foo; // Instantiate Jaccard Index metric
    return classification_base(actual, predicted, w, foo, micro, na_rm);
}

//' @rdname jaccard
//' @method jaccard cmatrix
//' @export
// [[Rcpp::export(jaccard.cmatrix)]]
NumericVector jaccard_cmatrix(const IntegerMatrix& x, Nullable<bool> micro = R_NilValue, const bool& na_rm = true) {
    JaccardIndexMetric foo; // Instantiate Jaccard Index metric
    return classification_base(x, foo, micro, na_rm);
}
