#include <Rcpp.h>
#include "regression_MeanAbsolutePercentageError.h"
using namespace Rcpp;

//' @rdname mape
//' @method mape numeric
//' @export
// [[Rcpp::export(mape.numeric)]]
double mape(
    const Rcpp::NumericVector& actual, 
    const Rcpp::NumericVector& predicted) {

        metric::MAPE<double> performance(actual, predicted);
        return performance.compute();
}

//' @rdname mape
//' @method weighted.mape numeric
//' @export
// [[Rcpp::export(weighted.mape.numeric)]]
double weighted_mape(
    const Rcpp::NumericVector& actual, 
    const Rcpp::NumericVector& predicted, 
    const Rcpp::NumericVector& w) {
        
        metric::weighted_MAPE<double> performance(actual, predicted, w);
        return performance.compute();
}
