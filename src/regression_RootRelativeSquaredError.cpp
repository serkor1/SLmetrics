#include <Rcpp.h>
#include "regression_RootRelativeSquaredError.h"
using namespace Rcpp;

//' @rdname rrse
//' @method rrse numeric
//' @export
// [[Rcpp::export(rrse.numeric)]]
double rrse(
    const Rcpp::NumericVector& actual, 
    const Rcpp::NumericVector& predicted) {
        
        metric::RRSE<double> performance(actual, predicted);
        return performance.compute();

}

//' @rdname rrse
//' @method weighted.rrse numeric
//' @export
// [[Rcpp::export(weighted.rrse.numeric)]]
double weighted_rrse(
    const Rcpp::NumericVector& actual, 
    const Rcpp::NumericVector& predicted, 
    const Rcpp::NumericVector& w) {

        metric::weighted_RRSE<double> performance(actual, predicted, w);
        return performance.compute();

}