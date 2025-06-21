#include "classification_DiagnosticOddsRatio.h"

// declare metric
using dor_impl = metric::diagnostic_odds_ratio<int>;

//' @templateVar .FUN dor
//' @templateVar .METHOD factor
//' @template classification_standard_inherit
//'
//' @export
// [[Rcpp::export(dor.factor)]]
double diagnostic_odds_ratio(
    const Rcpp::IntegerVector& actual,
    const Rcpp::IntegerVector& predicted) {

        dor_impl performance(actual, predicted);
        return performance.compute();
}

//' @templateVar .FUN weighted.dor
//' @templateVar .METHOD factor
//' @template classification_standard_inherit
//'
//' @export
// [[Rcpp::export(weighted.dor.factor)]]
double weighted_diagnostic_odds_ratio(
    const Rcpp::IntegerVector& actual,
    const Rcpp::IntegerVector& predicted,
    const Rcpp::NumericVector& w) {

        dor_impl performance(actual, predicted, w);
        return performance.compute();
}

//' @templateVar .FUN dor
//' @templateVar .METHOD cmatrix
//' @template classification_standard_inherit
//'
//' @export
// [[Rcpp::export(dor.cmatrix)]]
double cmatrix_diagnostic_odds_ratio(
    const Rcpp::NumericMatrix& x) {

        dor_impl performance(x);
        return performance.compute();
}
