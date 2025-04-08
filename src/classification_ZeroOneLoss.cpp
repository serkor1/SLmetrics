#include <Rcpp.h>
#include "classification_ZeroOneLoss.h"

using zero_one_loss_impl = metric::zerooneloss_score<int>;

//' @rdname zerooneloss
//' @method zerooneloss factor
//' @export
// [[Rcpp::export(zerooneloss.factor)]]
double zero_one_loss(
    const Rcpp::IntegerVector& actual, 
    const Rcpp::IntegerVector& predicted) {

        zero_one_loss_impl performance(actual, predicted);
        return performance.compute();
}

//' @rdname zerooneloss
//' @method weighted.zerooneloss factor
//' @export
// [[Rcpp::export(weighted.zerooneloss.factor)]]
double weighted_zero_one_loss(
    const Rcpp::IntegerVector& actual, 
    const Rcpp::IntegerVector& predicted, 
    const Rcpp::NumericVector& w) {

        zero_one_loss_impl performance(actual, predicted, w);
        return performance.compute();
}

//' @rdname zerooneloss
//' @method zerooneloss cmatrix
//' @export
// [[Rcpp::export(zerooneloss.cmatrix)]]
double cmatrix_zero_one_loss(
    const Rcpp::NumericMatrix& x) {

        zero_one_loss_impl performance(x);
        return performance.compute();
}