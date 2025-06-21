#include "regression_MeanArctangentAbsolutePercentageError.h"

//' @templateVar .FUN maape
//' @templateVar .METHOD numeric
//' @template regression_standard_inherit
//' @export
// [[Rcpp::export(maape.numeric)]]
double maape(
    const Rcpp::NumericVector& actual, 
    const Rcpp::NumericVector& predicted) {

        metric::MAAPE<double> performance(actual, predicted);
        return performance.compute();
}

//' @templateVar .FUN weighted.maape
//' @templateVar .METHOD numeric
//' @template regression_standard_inherit
//' @export
// [[Rcpp::export(weighted.maape.numeric)]]
double weighted_maape(
    const Rcpp::NumericVector& actual, 
    const Rcpp::NumericVector& predicted, 
    const Rcpp::NumericVector& w) {
        
        metric::weighted_MAAPE<double> performance(actual, predicted, w);
        return performance.compute();
}
