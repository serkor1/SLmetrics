#include "regression_MeanSquaredError.h"

//' @templateVar .FUN mse
//' @templateVar .METHOD numeric
//' @template regression_standard_inherit
//' @export
// [[Rcpp::export(mse.numeric)]]
double mse(
    const Rcpp::NumericVector& actual,
    const Rcpp::NumericVector& predicted) {

        // 1) define metric 
        // object
        metric::MSE<double> performance(actual, predicted);

        // 2) calculate 
        // value
        return performance.compute();
}

//' @templateVar .FUN weighted.mse
//' @templateVar .METHOD numeric
//' @template regression_standard_inherit
//' @export
// [[Rcpp::export(weighted.mse.numeric)]]
double weighted_mse(
    const Rcpp::NumericVector& actual, 
    const Rcpp::NumericVector& predicted,
    const Rcpp::NumericVector& w) {

        // 1) define metric 
        // object
        metric::weighted_MSE<double> performance(actual, predicted, w);

        // 2) calculate 
        // value
        return performance.compute();
   
}
