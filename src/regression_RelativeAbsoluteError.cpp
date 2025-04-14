#include <Rcpp.h>
#include "regression_RelativeAbsoluteError.h"
using namespace Rcpp;

//' @templateVar .FUN rae
//' @templateVar .METHOD numeric
//' @template regression_standard_inherit
//' @export
// [[Rcpp::export(rae.numeric)]]
double rae(
    const Rcpp::NumericVector& actual, 
    const Rcpp::NumericVector& predicted) {

        metric::RAE<double> performance(actual, predicted);
        return performance.compute();
}

//' @templateVar .FUN weighted.rae
//' @templateVar .METHOD numeric
//' @template regression_standard_inherit
//' @export
// [[Rcpp::export(weighted.rae.numeric)]]
double weighted_rae(
    const Rcpp::NumericVector& actual, 
    const Rcpp::NumericVector& predicted, 
    const Rcpp::NumericVector& w) {
        
        metric::weighted_RAE<double> performance(actual, predicted, w);
        return performance.compute(); 
}