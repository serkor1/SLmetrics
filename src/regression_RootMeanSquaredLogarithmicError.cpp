#include "regression_RootMeanSquaredLogarithmicError.h"

//' @templateVar .FUN rmsle
//' @templateVar .METHOD numeric
//' @template regression_standard_inherit
//' @export
// [[Rcpp::export(rmsle.numeric)]]
double rmsle(
    const Rcpp::NumericVector& actual, 
    const Rcpp::NumericVector& predicted) {

        metric::RMSLE<double> performance(actual, predicted);
        return performance.compute();
}

//' @templateVar .FUN weighted.rmsle
//' @templateVar .METHOD numeric
//' @template regression_standard_inherit
//' @export
// [[Rcpp::export(weighted.rmsle.numeric)]]
double weighted_rmsle(
    const Rcpp::NumericVector& actual,
    const Rcpp::NumericVector& predicted, 
    const Rcpp::NumericVector& w) {

        metric::weighted_RMSLE<double> performance(actual, predicted, w);
        return performance.compute();
}