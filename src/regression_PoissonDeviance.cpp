#include "SLmetrics.h"
#include "regression_PoissonDeviance.h"
using namespace Rcpp;

//' @templateVar .FUN poisson.deviance
//' @templateVar .METHOD numeric
//' @template regression_standard_inherit
//' @export
// [[Rcpp::export(poisson.deviance.numeric)]]
double poisson_deviance(
    const Rcpp::NumericVector& actual,
    const Rcpp::NumericVector& predicted) {

        // 1) define metric 
        // object
        metric::PoissonDeviance<double> performance(actual, predicted);

        // 2) calculate 
        // value
        return performance.compute();
}

//' @templateVar .FUN weighted.poisson.deviance
//' @templateVar .METHOD numeric
//' @template regression_standard_inherit
//' @export
// [[Rcpp::export(weighted.poisson.deviance.numeric)]]
double weighted_poisson_deviance(
    const Rcpp::NumericVector& actual, 
    const Rcpp::NumericVector& predicted,
    const Rcpp::NumericVector& w) {

        // 1) define metric 
        // object
        metric::weighted_PoissonDeviance<double> performance(actual, predicted, w);

        // 2) calculate 
        // value
        return performance.compute();
   
}