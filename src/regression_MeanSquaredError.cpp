#include <Rcpp.h>
#include "regression_MeanSquaredError.h"
using namespace Rcpp;

//' @rdname mse
//' @method mse numeric
//' @export
// [[Rcpp::export(mse.numeric)]]
double mse(
    const Rcpp::NumericVector& actual,
    const Rcpp::NumericVector& predicted) {

        // 1) define metric 
        // object
        metric::MSE<double> performance(actual, predicted);

        // 2) calculate 
        // value
        return performance.compute();
}

//' @rdname mse
//' @method weighted.mse numeric
//' @export
// [[Rcpp::export(weighted.mse.numeric)]]
double weighted_mse(
    const Rcpp::NumericVector& actual, 
    const Rcpp::NumericVector& predicted,
    const Rcpp::NumericVector& w) {

        // 1) define metric 
        // object
        metric::weighted_MSE<double> performance(actual, predicted, w);

        // 2) calculate 
        // value
        return performance.compute();
   
}
