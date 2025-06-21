#include "regression_ConcordanceCorrelationCoefficient.h"

//' @templateVar .FUN ccc
//' @templateVar .METHOD numeric
//' @template regression_standard_inherit
//' @export
// [[Rcpp::export(ccc.numeric)]]
double ccc(
    const Rcpp::NumericVector& actual,
    const Rcpp::NumericVector& predicted,
    bool correction = false) {

        metric::CCC<double> performance(actual, predicted, correction);
        return performance.compute();
}

//' @templateVar .FUN weighted.ccc
//' @templateVar .METHOD numeric
//' @template regression_standard_inherit
//' @export
// [[Rcpp::export(weighted.ccc.numeric)]]
double weighted_ccc(
    const Rcpp::NumericVector& actual,
    const Rcpp::NumericVector& predicted,
    const Rcpp::NumericVector& w,
    bool correction = false) {

        metric::weighted_CCC<double> performance(actual, predicted, w, correction);
        return performance.compute();
}
