#include "regression_TweedieDeviance.h"

//' @templateVar .FUN deviance.tweedie
//' @templateVar .METHOD numeric
//' @template regression_standard_inherit
//' @rawNamespace S3method(deviance.tweedie,numeric)
// [[Rcpp::export(deviance.tweedie.numeric)]]
double tweedie_deviance(
    const Rcpp::NumericVector& actual,
    const Rcpp::NumericVector& predicted,
    double power = 2.0) {

        // 1) define metric
        // object
        metric::TweedieDeviance<double> performance(actual, predicted, power);

        // 2) calculate
        // value
        return performance.compute();
}

//' @templateVar .FUN weighted.deviance.tweedie
//' @templateVar .METHOD numeric
//' @template regression_standard_inherit
//' @rawNamespace S3method(weighted.deviance.tweedie,numeric)
// [[Rcpp::export(weighted.deviance.tweedie.numeric)]]
double weighted_tweedie_deviance(
    const Rcpp::NumericVector& actual,
    const Rcpp::NumericVector& predicted,
    const Rcpp::NumericVector& w,
    double power = 2.0) {

        // 1) define metric
        // object
        metric::weighted_TweedieDeviance<double> performance(actual, predicted, w, power);

        // 2) calculate
        // value
        return performance.compute();

}
