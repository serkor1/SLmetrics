#include <Rcpp.h>
#include "classification_FBetaScore.h"

// declare metric;
using f_beta = metric::f_beta<int>;

//' @templateVar .TITLE fbeta
//' @templateVar .FUN fbeta
//' @templateVar .METHOD factor
//' @template classification_factor_example
//' @template classification_cmatrix_inherit
//'
//' @param beta A <[numeric]> vector of [length] \eqn{1} (default: \eqn{1}).
//'
//' @export
// [[Rcpp::export(fbeta.factor)]]
Rcpp::NumericVector fbeta_score(
    const Rcpp::IntegerVector& actual, 
    const Rcpp::IntegerVector& predicted, 
    const double& beta = 1.0, 
    const int& estimator = 0, 
    bool na_rm = true) {
        
        f_beta performance(actual, predicted, beta, static_cast<metric::aggregate>(estimator), na_rm);
        return performance.compute();
}

//' @templateVar .TITLE fbeta
//' @templateVar .FUN weighted.fbeta
//' @templateVar .METHOD factor
//' @template classification_factor_weighted_example
//' @template classification_cmatrix_inherit
//'
//' @param beta A <[numeric]> vector of [length] \eqn{1} (default: \eqn{1}).
//'
//' @export
// [[Rcpp::export(weighted.fbeta.factor)]]
Rcpp::NumericVector weighted_fbeta_score(
    const Rcpp::IntegerVector& actual, 
    const Rcpp::IntegerVector& predicted, 
    const Rcpp::NumericVector& w, 
    const double& beta = 1.0, 
    const int& estimator = 0, 
    bool na_rm = true) {

        f_beta performance(actual, predicted, w, beta, static_cast<metric::aggregate>(estimator), na_rm);
        return performance.compute();
}

//' @templateVar .TITLE fbeta
//' @templateVar .FUN fbeta
//' @templateVar .METHOD cmatrix
//' @template classification_cmatrix_example
//' @template classification_cmatrix_inherit
//'
//' @param beta A <[numeric]> vector of [length] \eqn{1} (default: \eqn{1}).
//'
//' @export
// [[Rcpp::export(fbeta.cmatrix)]]
Rcpp::NumericVector cmatrix_fbeta_score(
    const Rcpp::NumericMatrix& x,
    const double& beta = 1.0,
    const int& estimator = 0,
    bool na_rm = true) {
        
        f_beta performance(x, beta, static_cast<metric::aggregate>(estimator), na_rm);
        return performance.compute();
}