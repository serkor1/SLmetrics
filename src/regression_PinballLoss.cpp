#include "regression_PinballLoss.h"

//' @templateVar .FUN pinball
//' @templateVar .METHOD numeric
//' @template regression_standard_inherit
//' @export
// [[Rcpp::export(pinball.numeric)]]
double pinball(
    const Rcpp::NumericVector& actual,
    const Rcpp::NumericVector& predicted,
    double alpha = 0.5,
    bool deviance = false) {

        metric::pinball_loss<double> performance(actual, predicted, alpha, deviance);
        return performance.compute();
}

//' @templateVar .FUN weighted.pinball
//' @templateVar .METHOD numeric
//' @template regression_standard_inherit
//' @export
// [[Rcpp::export(weighted.pinball.numeric)]]
double weighted_pinball(
    const Rcpp::NumericVector& actual,
    const Rcpp::NumericVector& predicted,
    const Rcpp::NumericVector& w,
    double alpha = 0.5,
    bool deviance = false) {

        metric::weighted_pinball_loss<double> performance(actual, predicted, w, alpha, deviance);
        return performance.compute();
}
