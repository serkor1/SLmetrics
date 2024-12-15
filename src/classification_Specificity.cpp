// [[Rcpp::depends(RcppEigen)]]
#include <RcppEigen.h>
#include "classification_Specificity.h" // SpecificityMetric definition

using namespace Rcpp;

//' @rdname specificity
//' @method specificity factor
//' @export
// [[Rcpp::export(specificity.factor)]]
NumericVector specificity(const IntegerVector& actual, const IntegerVector& predicted, Nullable<bool> micro = R_NilValue, const bool& na_rm = true) {

    SpecificityMetric foo; // Instantiate SpecificityMetric
    return classification_base(actual, predicted, foo, micro, na_rm);
}

//' @rdname specificity
//' @method weighted.specificity factor
//' @export
// [[Rcpp::export(weighted.specificity.factor)]]
NumericVector weighted_specificity(const IntegerVector& actual, const IntegerVector& predicted, const NumericVector& w, Nullable<bool> micro = R_NilValue, const bool& na_rm = true) {
    SpecificityMetric foo; // Instantiate SpecificityMetric
    return classification_base(actual, predicted, w, foo, micro, na_rm);
}

//' @rdname specificity
//' @method specificity cmatrix
//' @export
// [[Rcpp::export(specificity.cmatrix)]]
NumericVector specificity_cmatrix(const IntegerMatrix& x, Nullable<bool> micro = R_NilValue, const bool& na_rm = true) {
    SpecificityMetric foo; // Instantiate SpecificityMetric
    return classification_base(x, foo, micro, na_rm);
}

//' @rdname specificity
//' @method tnr factor
//' @export
// [[Rcpp::export(tnr.factor)]]
NumericVector tnr(const IntegerVector& actual, const IntegerVector& predicted, Nullable<bool> micro = R_NilValue, const bool& na_rm = true) {
    SpecificityMetric foo; // Instantiate SpecificityMetric
    return classification_base(actual, predicted, foo, micro, na_rm);
}

//' @rdname specificity
//' @method weighted.tnr factor
//' @export
// [[Rcpp::export(weighted.tnr.factor)]]
NumericVector weighted_tnr(const IntegerVector& actual, const IntegerVector& predicted, const NumericVector& w, Nullable<bool> micro = R_NilValue, const bool& na_rm = true) {
    SpecificityMetric foo; // Instantiate SpecificityMetric
    return classification_base(actual, predicted, w, foo, micro, na_rm);
}

//' @rdname specificity
//' @method tnr cmatrix
//' @export
// [[Rcpp::export(tnr.cmatrix)]]
NumericVector tnr_cmatrix(const IntegerMatrix& x, Nullable<bool> micro = R_NilValue, const bool& na_rm = true) {
    SpecificityMetric foo; // Instantiate SpecificityMetric
    return classification_base(x, foo, micro, na_rm);
}

//' @rdname specificity
//' @method selectivity factor
//' @export
// [[Rcpp::export(selectivity.factor)]]
NumericVector selectivity(const IntegerVector& actual, const IntegerVector& predicted, Nullable<bool> micro = R_NilValue, const bool& na_rm = true) {
    SpecificityMetric foo; // Instantiate SpecificityMetric
    return classification_base(actual, predicted, foo, micro, na_rm);
}

//' @rdname specificity
//' @method weighted.selectivity factor
//' @export
// [[Rcpp::export(weighted.selectivity.factor)]]
NumericVector weighted_selectivity(const IntegerVector& actual, const IntegerVector& predicted, const NumericVector& w, Nullable<bool> micro = R_NilValue, const bool& na_rm = true) {
    SpecificityMetric foo; // Instantiate SpecificityMetric
    return classification_base(actual, predicted, w, foo, micro, na_rm);
}

//' @rdname specificity
//' @method selectivity cmatrix
//' @export
// [[Rcpp::export(selectivity.cmatrix)]]
NumericVector selectivity_cmatrix(const IntegerMatrix& x, Nullable<bool> micro = R_NilValue, const bool& na_rm = true) {
    SpecificityMetric foo; // Instantiate SpecificityMetric
    return classification_base(x, foo, micro, na_rm);
}
