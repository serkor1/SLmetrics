#include "regression_RelativeRootMeanSquaredError.h"

//' @templateVar .FUN rrmse
//' @templateVar .METHOD numeric
//' @template regression_standard_inherit
//' @export
// [[Rcpp::export(rrmse.numeric)]]
double RelativeRootMeanSquaredError(
    const Rcpp::NumericVector& actual, 
    const Rcpp::NumericVector& predicted, 
    const int normalization = 1) {

        metric::RRMSE<double> performance(actual, predicted, normalization);
        return performance.compute();
}

//' @templateVar .FUN weighted.rrmse
//' @templateVar .METHOD numeric
//' @template regression_standard_inherit
//' @export
// [[Rcpp::export(weighted.rrmse.numeric)]]
double weighted_RelativeRootMeanSquaredError(
    const Rcpp::NumericVector& actual, 
    const Rcpp::NumericVector& predicted, 
    const Rcpp::NumericVector& w, 
    const int normalization = 1) {

        metric::weighted_RRMSE<double> performance(actual, predicted, w, normalization);
        return performance.compute();
}
