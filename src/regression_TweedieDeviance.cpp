#include "SLmetrics.h"
#include "regression_TweedieDeviance.h"
using namespace Rcpp;

//' @templateVar .FUN tweedie.deviance
//' @templateVar .METHOD numeric
//' @template regression_standard_inherit
//' @export
// [[Rcpp::export(tweedie.deviance.numeric)]]
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

//' @templateVar .FUN weighted.tweedie.deviance
//' @templateVar .METHOD numeric
//' @template regression_standard_inherit
//' @export
// [[Rcpp::export(weighted.tweedie.deviance.numeric)]]
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
