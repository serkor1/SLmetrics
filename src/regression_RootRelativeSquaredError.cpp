#include <Rcpp.h>
#include "regression_RootRelativeSquaredError.h"
using namespace Rcpp;

//' @templateVar .FUN rrse
//' @templateVar .METHOD numeric
//' @template regression_standard_inherit
//' @export
// [[Rcpp::export(rrse.numeric)]]
double rrse(
    const Rcpp::NumericVector& actual, 
    const Rcpp::NumericVector& predicted) {
        
        metric::RRSE<double> performance(actual, predicted);
        return performance.compute();

}

//' @templateVar .FUN weighted.rrse
//' @templateVar .METHOD numeric
//' @template regression_standard_inherit
//' @export
// [[Rcpp::export(weighted.rrse.numeric)]]
double weighted_rrse(
    const Rcpp::NumericVector& actual, 
    const Rcpp::NumericVector& predicted, 
    const Rcpp::NumericVector& w) {

        metric::weighted_RRSE<double> performance(actual, predicted, w);
        return performance.compute();

}