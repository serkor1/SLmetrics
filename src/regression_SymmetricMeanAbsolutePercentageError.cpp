#include "regression_SymmetricMeanAbsolutePercentageError.h"

//' @templateVar .FUN smape
//' @templateVar .METHOD numeric
//' @template regression_standard_inherit
//' @export
// [[Rcpp::export(smape.numeric)]]
double smape(
    const Rcpp::NumericVector& actual, 
    const Rcpp::NumericVector& predicted) {

        metric::SMAPE<double> performance(actual, predicted);
        return performance.compute();
}

//' @templateVar .FUN weighted.smape
//' @templateVar .METHOD numeric
//' @template regression_standard_inherit
//' @export
// [[Rcpp::export(weighted.smape.numeric)]]
double weighted_smape(
    const Rcpp::NumericVector& actual, 
    const Rcpp::NumericVector& predicted, 
    const Rcpp::NumericVector& w) {
        
        metric::weighted_SMAPE<double> performance(actual, predicted, w);
        return performance.compute();
}
