#include <Rcpp.h>
#include "classification_ZeroOneLoss.h"

using zero_one_loss_impl = metric::zerooneloss_score<int>;

//' @templateVar .TITLE zerooneloss
//' @templateVar .FUN zerooneloss
//' @templateVar .METHOD factor
//' @template classification_factor_example
//' @template classification_cmatrix_inherit
//'
//' @export
// [[Rcpp::export(zerooneloss.factor)]]
double zero_one_loss(
    const Rcpp::IntegerVector& actual, 
    const Rcpp::IntegerVector& predicted) {

        zero_one_loss_impl performance(actual, predicted);
        return performance.compute();
}

//' @templateVar .TITLE zerooneloss
//' @templateVar .FUN weighted.zerooneloss
//' @templateVar .METHOD factor
//' @template classification_factor_weighted_example
//' @template classification_cmatrix_inherit
//'
//' @export
// [[Rcpp::export(weighted.zerooneloss.factor)]]
double weighted_zero_one_loss(
    const Rcpp::IntegerVector& actual, 
    const Rcpp::IntegerVector& predicted, 
    const Rcpp::NumericVector& w) {

        zero_one_loss_impl performance(actual, predicted, w);
        return performance.compute();
}

//' @templateVar .TITLE zerooneloss
//' @templateVar .FUN zerooneloss
//' @templateVar .METHOD cmatrix
//' @template classification_cmatrix_example
//' @template classification_cmatrix_inherit
//'
//' @export
// [[Rcpp::export(zerooneloss.cmatrix)]]
double cmatrix_zero_one_loss(
    const Rcpp::NumericMatrix& x) {

        zero_one_loss_impl performance(x);
        return performance.compute();
}