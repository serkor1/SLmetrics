#include <Rcpp.h>
#include "classification_Precision.h"

// declare metric
using precision_impl = metric::precision<int>;

//' @rdname precision
//' @method precision factor
//' @export
// [[Rcpp::export(precision.factor)]]
Rcpp::NumericVector precision(
    const Rcpp::IntegerVector& actual, 
    const Rcpp::IntegerVector& predicted, 
    const int& estimator = 0, 
    bool na_rm = true) {
        
        precision_impl performance(actual, predicted, static_cast<metric::aggregate>(estimator), na_rm);
        return performance.compute();
}

//' @rdname precision
//' @method weighted.precision factor
//' @export
// [[Rcpp::export(weighted.precision.factor)]]
Rcpp::NumericVector weighted_precision(
    const Rcpp::IntegerVector& actual, 
    const Rcpp::IntegerVector& predicted, 
    const Rcpp::NumericVector& w, 
    const int& estimator = 0, 
    bool na_rm = true) {

        precision_impl performance(actual, predicted, w, static_cast<metric::aggregate>(estimator), na_rm);
        return performance.compute();
}

//' @rdname precision
//' @method precision cmatrix
//' @export
// [[Rcpp::export(precision.cmatrix)]]
Rcpp::NumericVector cmatrix_precision(
    const Rcpp::NumericMatrix& x,
    const int& estimator = 0,
    bool na_rm = true) {
        
        precision_impl performance(x, static_cast<metric::aggregate>(estimator), na_rm);
        return performance.compute();
}

//' @rdname precision
//' @method ppv factor
//' @export
// [[Rcpp::export(ppv.factor)]]
Rcpp::NumericVector ppv(
    const Rcpp::IntegerVector& actual, 
    const Rcpp::IntegerVector& predicted, 
    const int& estimator = 0, 
    bool na_rm = true) {
        
        precision_impl performance(actual, predicted, static_cast<metric::aggregate>(estimator), na_rm);
        return performance.compute();
}

//' @rdname precision
//' @method weighted.ppv factor
//' @export
// [[Rcpp::export(weighted.ppv.factor)]]
Rcpp::NumericVector weighted_ppv_score(
    const Rcpp::IntegerVector& actual, 
    const Rcpp::IntegerVector& predicted, 
    const Rcpp::NumericVector& w, 
    const int& estimator = 0, 
    bool na_rm = true) {

        precision_impl performance(actual, predicted, w, static_cast<metric::aggregate>(estimator), na_rm);
        return performance.compute();
}

//' @rdname precision
//' @method ppv cmatrix
//' @export
// [[Rcpp::export(ppv.cmatrix)]]
Rcpp::NumericVector cmatrix_ppv_score(
    const Rcpp::NumericMatrix& x,
    const int& estimator = 0,
    bool na_rm = true) {
        
        precision_impl performance(x, static_cast<metric::aggregate>(estimator), na_rm);
        return performance.compute();
}