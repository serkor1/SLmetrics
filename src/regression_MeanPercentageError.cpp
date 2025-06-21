#include "regression_MeanPercentageError.h"

//' @templateVar .FUN mpe
//' @templateVar .METHOD numeric
//' @template regression_standard_inherit
//' @export
// [[Rcpp::export(mpe.numeric)]]
double mpe(
    const Rcpp::NumericVector& actual,
    const Rcpp::NumericVector& predicted) {

        metric::MPE<double> performance(actual, predicted);
        return performance.compute();
}

//' @templateVar .FUN weighted.mpe
//' @templateVar .METHOD numeric
//' @template regression_standard_inherit
//' @export
// [[Rcpp::export(weighted.mpe.numeric)]]
double weighted_mpe(
    const Rcpp::NumericVector& actual,
    const Rcpp::NumericVector& predicted,
    const Rcpp::NumericVector& w) {

        metric::weighted_MPE<double> performance(actual, predicted, w);
        return performance.compute();
}
