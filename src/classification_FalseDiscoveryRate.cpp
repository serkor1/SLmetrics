#include <Rcpp.h>
#include "classification_FalseDiscoveryRate.h"

// declare metric
using fdr_impl = metric::false_discovery_rate<int>;

//' @templateVar .TITLE fdr
//' @templateVar .FUN fdr
//' @templateVar .METHOD factor
//' @template classification_factor_example
//' @template classification_cmatrix_inherit
//'
//' @export
// [[Rcpp::export(fdr.factor)]]
Rcpp::NumericVector false_discovery_rate(
    const Rcpp::IntegerVector& actual, 
    const Rcpp::IntegerVector& predicted, 
    const int& estimator = 0, 
    bool na_rm = true) {
        
        fdr_impl performance(actual, predicted, static_cast<metric::aggregate>(estimator), na_rm);
        return performance.compute();
}

//' @templateVar .TITLE fdr
//' @templateVar .FUN weighted.fdr
//' @templateVar .METHOD factor
//' @template classification_factor_weighted_example
//' @template classification_cmatrix_inherit
//'
//' @export
// [[Rcpp::export(weighted.fdr.factor)]]
Rcpp::NumericVector weighted_false_discovery_rate(
    const Rcpp::IntegerVector& actual, 
    const Rcpp::IntegerVector& predicted, 
    const Rcpp::NumericVector& w, 
    const int& estimator = 0, 
    bool na_rm = true) {

        fdr_impl performance(actual, predicted, w, static_cast<metric::aggregate>(estimator), na_rm);
        return performance.compute();
}

//' @templateVar .TITLE fdr
//' @templateVar .FUN fdr
//' @templateVar .METHOD cmatrix
//' @template classification_cmatrix_example
//' @template classification_cmatrix_inherit
//'
//' @export
// [[Rcpp::export(fdr.cmatrix)]]
Rcpp::NumericVector cmatrix_false_discovery_rate(
    const Rcpp::NumericMatrix& x,
    const int& estimator = 0,
    bool na_rm = true) {
        
        fdr_impl performance(x, static_cast<metric::aggregate>(estimator), na_rm);
        return performance.compute();
}