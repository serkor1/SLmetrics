#include "regression_RootMeanSquaredError.h"

//' @templateVar .FUN rmse
//' @templateVar .METHOD numeric
//' @template regression_standard_inherit
//' @export
// [[Rcpp::export(rmse.numeric)]]
double rmse(
    const Rcpp::NumericVector& actual,
    const Rcpp::NumericVector& predicted) {

        // 1) define metric 
        // object
        metric::RMSE<double> performance(actual, predicted);

        // 2) calculate 
        // value
        return performance.compute();
}

//' @templateVar .FUN weighted.rmse
//' @templateVar .METHOD numeric
//' @template regression_standard_inherit
//' @export
// [[Rcpp::export(weighted.rmse.numeric)]]
double weighted_rmse(
    const Rcpp::NumericVector& actual, 
    const Rcpp::NumericVector& predicted,
    const Rcpp::NumericVector& w) {

        // 1) define metric 
        // object
        metric::weighted_RMSE<double> performance(actual, predicted, w);

        // 2) calculate 
        // value
        return performance.compute();
   
}
