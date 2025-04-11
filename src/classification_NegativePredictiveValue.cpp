#include <Rcpp.h>
#include "classification_NegativePredictiveValue.h"

// declare metric
using npv_impl = metric::negative_predictive_value<int>;

//' @templateVar .TITLE npv
//' @templateVar .FUN npv
//' @templateVar .METHOD factor
//' @template classification_factor_example
//' @template classification_cmatrix_inherit
//'
//' @export
// [[Rcpp::export(npv.factor)]]
Rcpp::NumericVector negative_predictive_value(
    const Rcpp::IntegerVector& actual, 
    const Rcpp::IntegerVector& predicted, 
    const int& estimator = 0, 
    bool na_rm = true) {
        
        npv_impl performance(actual, predicted, static_cast<metric::aggregate>(estimator), na_rm);
        return performance.compute();
}

//' @templateVar .TITLE npv
//' @templateVar .FUN weighted.npv
//' @templateVar .METHOD factor
//' @template classification_factor_weighted_example
//' @template classification_cmatrix_inherit
//'
//' @export
// [[Rcpp::export(weighted.npv.factor)]]
Rcpp::NumericVector weighted_negative_predictive_value(
    const Rcpp::IntegerVector& actual, 
    const Rcpp::IntegerVector& predicted, 
    const Rcpp::NumericVector& w, 
    const int& estimator = 0, 
    bool na_rm = true) {

        npv_impl performance(actual, predicted, w, static_cast<metric::aggregate>(estimator), na_rm);
        return performance.compute();
}

//' @templateVar .TITLE npv
//' @templateVar .FUN npv
//' @templateVar .METHOD cmatrix
//' @template classification_cmatrix_example
//' @template classification_cmatrix_inherit
//'
//' @export
// [[Rcpp::export(npv.cmatrix)]]
Rcpp::NumericVector cmatrix_negative_predictive_value(
    const Rcpp::NumericMatrix& x,
    const int& estimator = 0,
    bool na_rm = true) {
        
        npv_impl performance(x, static_cast<metric::aggregate>(estimator), na_rm);
        return performance.compute();
}