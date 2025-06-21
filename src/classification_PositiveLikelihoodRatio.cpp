#include "classification_PositiveLikelihoodRatio.h"

// declare metric
using plr = metric::positive_likelihood_ratio<int>;

//' @templateVar .FUN plr
//' @templateVar .METHOD factor
//' @template classification_standard_inherit
//'
//' @export
// [[Rcpp::export(plr.factor)]]
double positive_likelihood_ratio(
    const Rcpp::IntegerVector& actual,
    const Rcpp::IntegerVector& predicted) {

        plr performance(actual, predicted);
        return performance.compute();
}

//' @templateVar .FUN weighted.plr
//' @templateVar .METHOD factor
//' @template classification_standard_inherit
//'
//' @export
// [[Rcpp::export(weighted.plr.factor)]]
double weighted_positive_likelihood_ratio(
    const Rcpp::IntegerVector& actual,
    const Rcpp::IntegerVector& predicted,
    const Rcpp::NumericVector& w) {

        plr performance(actual, predicted, w);
        return performance.compute();
}

//' @templateVar .FUN plr
//' @templateVar .METHOD cmatrix
//' @template classification_standard_inherit
//'
//' @export
// [[Rcpp::export(plr.cmatrix)]]
double cmatrix_positive_likelihood_ratio(
    const Rcpp::NumericMatrix& x) {

        plr performance(x);
        return performance.compute();
}
