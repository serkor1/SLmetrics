#include <Rcpp.h>
#include "classification_FalseOmissionRate.h"

// declare metric
using fer_impl = metric::false_omission_rate<int>;

//' @rdname fer
//' @method fer factor
//' @export
// [[Rcpp::export(fer.factor)]]
Rcpp::NumericVector false_omission_rate(
    const Rcpp::IntegerVector& actual, 
    const Rcpp::IntegerVector& predicted, 
    const int& estimator = 0, 
    bool na_rm = true) {
        
        fer_impl performance(actual, predicted, static_cast<metric::aggregate>(estimator), na_rm);
        return performance.compute();
}

//' @rdname fer
//' @method weighted.fer factor
//' @export
// [[Rcpp::export(weighted.fer.factor)]]
Rcpp::NumericVector weighted_false_omission_rate(
    const Rcpp::IntegerVector& actual, 
    const Rcpp::IntegerVector& predicted, 
    const Rcpp::NumericVector& w, 
    const int& estimator = 0, 
    bool na_rm = true) {

        fer_impl performance(actual, predicted, w, static_cast<metric::aggregate>(estimator), na_rm);
        return performance.compute();
}

//' @rdname fer
//' @method fer cmatrix
//' @export
// [[Rcpp::export(fer.cmatrix)]]
Rcpp::NumericVector cmatrix_false_omission_rate(
    const Rcpp::NumericMatrix& x,
    const int& estimator = 0,
    bool na_rm = true) {
        
        fer_impl performance(x, static_cast<metric::aggregate>(estimator), na_rm);
        return performance.compute();
}