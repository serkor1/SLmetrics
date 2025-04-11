#include <Rcpp.h>
#include "classification_HammingLoss.h"

using hamming_loss_t = metric::hamming_loss<int>;

//' @templateVar .TITLE hammingloss
//' @templateVar .FUN hammingloss
//' @templateVar .METHOD factor
//' @template classification_factor_example
//' @template classification_cmatrix_inherit
//'
//' @export
// [[Rcpp::export(hammingloss.factor)]]
double hamming_loss(
    const Rcpp::IntegerVector& actual, 
    const Rcpp::IntegerVector& predicted) {

        hamming_loss_t performance(actual, predicted);
        return performance.compute();
}

//' @templateVar .TITLE hammingloss
//' @templateVar .FUN weighted.hammingloss
//' @templateVar .METHOD factor
//' @template classification_factor_weighted_example
//' @template classification_cmatrix_inherit
//'
//' @export
// [[Rcpp::export(weighted.hammingloss.factor)]]
double weighted_hamming_loss(
    const Rcpp::IntegerVector& actual, 
    const Rcpp::IntegerVector& predicted, 
    const Rcpp::NumericVector& w) {

        hamming_loss_t performance(actual, predicted, w);
        return performance.compute();
}

//' @templateVar .TITLE hammingloss
//' @templateVar .FUN hammingloss
//' @templateVar .METHOD cmatrix
//' @template classification_cmatrix_example
//' @template classification_cmatrix_inherit
//'
//' @export
// [[Rcpp::export(hammingloss.cmatrix)]]
double cmatrix_hamming_loss(
    const Rcpp::NumericMatrix& x) {

        hamming_loss_t performance(x);
        return performance.compute();
}