#include "regression_HuberLoss.h"

//' @templateVar .FUN huberloss
//' @templateVar .METHOD numeric
//' @template regression_standard_inherit
//' @export
// [[Rcpp::export(huberloss.numeric)]]
double huberloss(
    const Rcpp::NumericVector& actual, 
    const Rcpp::NumericVector& predicted, 
    double delta = 1.0) {

        metric::huberloss<double> performance(actual, predicted, delta);
        return performance.compute();

}

//' @templateVar .FUN weighted.huberloss
//' @templateVar .METHOD numeric
//' @template regression_standard_inherit
//' @export
// [[Rcpp::export(weighted.huberloss.numeric)]]
double weighted_huberloss(
    const Rcpp::NumericVector& actual, 
    const Rcpp::NumericVector& predicted, 
    const Rcpp::NumericVector& w, 
    double delta = 1.0) {

        metric::weighted_huberloss<double> performance(actual, predicted, w, delta);
        return performance.compute();
}