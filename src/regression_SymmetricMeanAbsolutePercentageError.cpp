#include <Rcpp.h>
#include "regression_SymmetricMeanAbsolutePercentageError.h"
using namespace Rcpp;

//' @rdname smape
//' @method smape numeric
//' @export
// [[Rcpp::export(smape.numeric)]]
double smape(
    const Rcpp::NumericVector& actual, 
    const Rcpp::NumericVector& predicted) {

        metric::SMAPE<double> performance(actual, predicted);
        return performance.compute();
}

//' @rdname smape
//' @method weighted.smape numeric
//' @export
// [[Rcpp::export(weighted.smape.numeric)]]
double weighted_smape(
    const Rcpp::NumericVector& actual, 
    const Rcpp::NumericVector& predicted, 
    const Rcpp::NumericVector& w) {
        
        metric::weighted_SMAPE<double> performance(actual, predicted, w);
        return performance.compute();
}
