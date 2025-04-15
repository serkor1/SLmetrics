#include "SLmetrics.h"
#include "regression_GammaDeviance.h"
using namespace Rcpp;

//' @templateVar .FUN gamma.deviance
//' @templateVar .METHOD numeric
//' @template regression_standard_inherit
//' @export
// [[Rcpp::export(gamma.deviance.numeric)]]
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

//' @templateVar .FUN weighted.gamma.deviance
//' @templateVar .METHOD numeric
//' @template regression_standard_inherit
//' @export
// [[Rcpp::export(weighted.gamma.deviance.numeric)]]
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