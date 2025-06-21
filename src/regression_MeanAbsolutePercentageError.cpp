#include "regression_MeanAbsolutePercentageError.h"

//' @templateVar .FUN mape
//' @templateVar .METHOD numeric
//' @template regression_standard_inherit
//' @export
// [[Rcpp::export(mape.numeric)]]
double mape(
    const Rcpp::NumericVector& actual, 
    const Rcpp::NumericVector& predicted) {

        metric::MAPE<double> performance(actual, predicted);
        return performance.compute();
}

//' @templateVar .FUN weighted.mape
//' @templateVar .METHOD numeric
//' @template regression_standard_inherit
//' @export
// [[Rcpp::export(weighted.mape.numeric)]]
double weighted_mape(
    const Rcpp::NumericVector& actual, 
    const Rcpp::NumericVector& predicted, 
    const Rcpp::NumericVector& w) {
        
        metric::weighted_MAPE<double> performance(actual, predicted, w);
        return performance.compute();
}
