#include <Rcpp.h>
#include "regression_MeanAbsoluteError.h"
using namespace Rcpp;

//' @rdname mae
//' @method mae numeric
//' @export
// [[Rcpp::export(mae.numeric)]]
double mae(
    const Rcpp::NumericVector& actual, 
    const Rcpp::NumericVector& predicted) {

        metric::MAE<double> performance(actual, predicted);
        return performance.compute();
}

//' @rdname mae
//' @method weighted.mae numeric
//' @export
// [[Rcpp::export(weighted.mae.numeric)]]
double weighted_mae(
    const Rcpp::NumericVector& actual, 
    const Rcpp::NumericVector& predicted, 
    const Rcpp::NumericVector& w) {

        metric::weighted_MAE<double> performance(actual, predicted, w);
        return performance.compute();

}