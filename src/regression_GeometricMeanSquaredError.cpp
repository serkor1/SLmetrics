#include "regression_GeometricMeanSquaredError.h"

//' @templateVar .FUN gmse
//' @templateVar .METHOD numeric
//' @template regression_standard_inherit
//' @export
// [[Rcpp::export(gmse.numeric)]]
double gmse(
    const Rcpp::NumericVector& actual,
    const Rcpp::NumericVector& predicted) {

        // 1) define metric 
        // object
        metric::gmse<double> performance(actual, predicted);

        // 2) calculate 
        // value
        return performance.compute();
}

//' @templateVar .FUN weighted.gmse
//' @templateVar .METHOD numeric
//' @template regression_standard_inherit
//' @export
// [[Rcpp::export(weighted.gmse.numeric)]]
double weighted_gmse(
    const Rcpp::NumericVector& actual, 
    const Rcpp::NumericVector& predicted,
    const Rcpp::NumericVector& w) {

        // 1) define metric 
        // object
        metric::weighted_gmse<double> performance(actual, predicted, w);

        // 2) calculate 
        // value
        return performance.compute();
   
}
