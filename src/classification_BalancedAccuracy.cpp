#include <Rcpp.h>
#include "classification_BalancedAccuracy.h"

// implementation of metric
using balanced_accuracy_score_impl = metric::balanced_accuracy_score<int>;

//' @rdname baccuracy
//' @method baccuracy factor
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

//' @rdname baccuracy
//' @method weighted.baccuracy factor
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

//' @rdname baccuracy
//' @method baccuracy cmatrix
//' @export
// [[Rcpp::export(baccuracy.cmatrix)]]
double cmatrix_balanced_accuracy(
    const Rcpp::NumericMatrix& x,
    const bool& adjust = false,
    bool na_rm = true) {

        balanced_accuracy_score_impl performance(x, adjust, na_rm);
        return performance.compute();
}