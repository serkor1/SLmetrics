#include <Rcpp.h>
#include "regression_RootMeanSquaredLogarithmicError.h"
using namespace Rcpp;

//' @rdname rmsle
//' @method rmsle numeric
//' @export
// [[Rcpp::export(rmsle.numeric)]]
double rmsle(
    const Rcpp::NumericVector& actual, 
    const Rcpp::NumericVector& predicted) {

        metric::RMSLE<double> performance(actual, predicted);
        return performance.compute();
}

//' @rdname rmsle
//' @method weighted.rmsle numeric
//' @export
// [[Rcpp::export(weighted.rmsle.numeric)]]
double weighted_rmsle(
    const Rcpp::NumericVector& actual,
    const Rcpp::NumericVector& predicted, 
    const Rcpp::NumericVector& w) {

        metric::weighted_RMSLE<double> performance(actual, predicted, w);
        return performance.compute();
}