#include "classification_BalancedAccuracy.h"

// implementation of metric
using balanced_accuracy_score_impl = metric::balanced_accuracy_score<int>;

//' @templateVar .FUN baccuracy
//' @templateVar .METHOD factor
//' @template classification_standard_inherit
//'
//' @param adjust A <[logical]> value (default: [FALSE]). If [TRUE] the metric is adjusted for random chance \eqn{\frac{1}{k}}.
//'
//' @export
// [[Rcpp::export(baccuracy.factor)]]
double balanced_accuracy(
    const Rcpp::IntegerVector& actual, 
    const Rcpp::IntegerVector& predicted,
    const bool& adjust = false,
    bool na_rm = true) {

        balanced_accuracy_score_impl performance(actual, predicted, adjust, na_rm);
        return performance.compute();
}

//' @templateVar .FUN weighted.baccuracy
//' @templateVar .METHOD factor
//' @template classification_standard_inherit
//'
//' @param adjust A <[logical]> value (default: [FALSE]). If [TRUE] the metric is adjusted for random chance \eqn{\frac{1}{k}}.
//'
//' @export
// [[Rcpp::export(weighted.baccuracy.factor)]]
double weighted_balanced_accuracy(
    const Rcpp::IntegerVector& actual, 
    const Rcpp::IntegerVector& predicted, 
    const Rcpp::NumericVector& w,
    const bool& adjust = false,
    bool na_rm = true) {

        balanced_accuracy_score_impl performance(actual, predicted, w, adjust, na_rm);
        return performance.compute();
}

//' @templateVar .FUN baccuracy
//' @templateVar .METHOD cmatrix
//' @template classification_standard_inherit
//'
//' @param adjust A <[logical]> value (default: [FALSE]). If [TRUE] the metric is adjusted for random chance \eqn{\frac{1}{k}}.
//'
//' @export
// [[Rcpp::export(baccuracy.cmatrix)]]
double cmatrix_balanced_accuracy(
    const Rcpp::NumericMatrix& x,
    const bool& adjust = false,
    bool na_rm = true) {

        balanced_accuracy_score_impl performance(x, adjust, na_rm);
        return performance.compute();
}