#include "regression_GammaDeviance.h"

//' @templateVar .FUN deviance.gamma
//' @templateVar .METHOD numeric
//' @template regression_standard_inherit
//' @rawNamespace S3method(deviance.gamma,numeric)
// [[Rcpp::export(deviance.gamma.numeric)]]
double gamma_deviance(
    const Rcpp::NumericVector& actual,
    const Rcpp::NumericVector& predicted) {

        // 1) define metric 
        // object
        metric::GammaDeviance<double> performance(actual, predicted);

        // 2) calculate 
        // value
        return performance.compute();
}

//' @templateVar .FUN weighted.deviance.gamma
//' @templateVar .METHOD numeric
//' @template regression_standard_inherit
//' @rawNamespace S3method(weighted.deviance.gamma,numeric)
// [[Rcpp::export(weighted.deviance.gamma.numeric)]]
double weighted_gamma_deviance(
    const Rcpp::NumericVector& actual, 
    const Rcpp::NumericVector& predicted,
    const Rcpp::NumericVector& w) {

        // 1) define metric 
        // object
        metric::weighted_GammaDeviance<double> performance(actual, predicted, w);

        // 2) calculate 
        // value
        return performance.compute();
   
}