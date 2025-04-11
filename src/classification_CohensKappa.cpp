#include <Rcpp.h>
#include "classification_CohensKappa.h"

// implementation of metric
using cohens_kappa_impl = metric::cohens_kappa<int>;

//' @templateVar .TITLE ckappa
//' @templateVar .FUN ckappa
//' @templateVar .METHOD factor
//' @template classification_factor_example
//' @template classification_cmatrix_inherit
//'
//' @param beta A <[numeric]> value of [length] 1 (default: 0). If \eqn{\beta \neq 0} the off-diagonals of the confusion matrix are penalized with a factor of \eqn{(y_{+} - y_{i,-})^\beta}.
//'
//'
//' @export
// [[Rcpp::export(ckappa.factor)]]
double cohens_kappa(
    const Rcpp::IntegerVector& actual, 
    const Rcpp::IntegerVector& predicted,
    const double& beta = 0.0) {

        cohens_kappa_impl performance(actual, predicted, beta);
        return performance.compute();
}

//' @templateVar .TITLE ckappa
//' @templateVar .FUN weighted.ckappa
//' @templateVar .METHOD factor
//' @template classification_factor_weighted_example
//' @template classification_cmatrix_inherit
//'
//' @param beta A <[numeric]> value of [length] 1 (default: 0). If \eqn{\beta \neq 0} the off-diagonals of the confusion matrix are penalized with a factor of \eqn{(y_{+} - y_{i,-})^\beta}.
//'
//' @export
// [[Rcpp::export(weighted.ckappa.factor)]]
double weighted_cohens_kappa(
    const Rcpp::IntegerVector& actual, 
    const Rcpp::IntegerVector& predicted, 
    const Rcpp::NumericVector& w,
    const double& beta = 0.0) {

        cohens_kappa_impl performance(actual, predicted, w, beta);
        return performance.compute();
}

//' @templateVar .TITLE ckappa
//' @templateVar .FUN ckappa
//' @templateVar .METHOD cmatrix
//' @template classification_cmatrix_example
//' @template classification_cmatrix_inherit
//'
//' @param beta A <[numeric]> value of [length] 1 (default: 0). If \eqn{\beta \neq 0} the off-diagonals of the confusion matrix are penalized with a factor of \eqn{(y_{+} - y_{i,-})^\beta}.
//'
//' @export
// [[Rcpp::export(ckappa.cmatrix)]]
double cmatrix_cohens_kappa(
    const Rcpp::NumericMatrix& x,
    const double& beta = 0.0) {

        cohens_kappa_impl performance(x, beta);
        return performance.compute();
}