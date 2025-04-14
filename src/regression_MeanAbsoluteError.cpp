#include <Rcpp.h>
#include "regression_MeanAbsoluteError.h"
using namespace Rcpp;

//' @templateVar .FUN mae
//' @templateVar .METHOD numeric
//' @template regression_standard_inherit
//' @export
// [[Rcpp::export(mae.numeric)]]
double mae(
    const Rcpp::NumericVector& actual, 
    const Rcpp::NumericVector& predicted) {

        metric::MAE<double> performance(actual, predicted);
        return performance.compute();
}

//' @templateVar .FUN weighted.mae
//' @templateVar .METHOD numeric
//' @template regression_standard_inherit
//' @export
// [[Rcpp::export(weighted.mae.numeric)]]
double weighted_mae(
    const Rcpp::NumericVector& actual, 
    const Rcpp::NumericVector& predicted, 
    const Rcpp::NumericVector& w) {

        metric::weighted_MAE<double> performance(actual, predicted, w);
        return performance.compute();

}