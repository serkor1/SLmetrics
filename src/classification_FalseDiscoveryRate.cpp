#include <Rcpp.h>
#include "classification_FalseDiscoveryRate.h"

// declare metric
using fdr_impl = metric::false_discovery_rate<int>;

//' @rdname fdr
//' @method fdr factor
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

//' @rdname fdr
//' @method weighted.fdr factor
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

//' @rdname fdr
//' @method fdr cmatrix
//' @export
// [[Rcpp::export(fdr.cmatrix)]]
Rcpp::NumericVector cmatrix_false_discovery_rate(
    const Rcpp::NumericMatrix& x,
    const int& estimator = 0,
    bool na_rm = true) {
        
        fdr_impl performance(x, static_cast<metric::aggregate>(estimator), na_rm);
        return performance.compute();
}