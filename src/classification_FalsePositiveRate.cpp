#include "classification_FalsePositiveRate.h"

// declare metric
using fpr = metric::false_positive_rate<int>;

//' @templateVar .FUN fpr
//' @templateVar .METHOD factor
//' @template classification_standard_inherit
//'
//' @export
// [[Rcpp::export(fpr.factor)]]
Rcpp::NumericVector false_positive_rate(
    const Rcpp::IntegerVector& actual, 
    const Rcpp::IntegerVector& predicted, 
    const int& estimator = 0, 
    const bool& na_rm = true) {
        
        fpr performance(actual, predicted, static_cast<metric::aggregate>(estimator), na_rm);
        return performance.compute();
}

//' @templateVar .FUN weighted.fpr
//' @templateVar .METHOD factor
//' @template classification_standard_inherit
//'
//' @export
// [[Rcpp::export(weighted.fpr.factor)]]
Rcpp::NumericVector weighted_false_positive_rate(
    const Rcpp::IntegerVector& actual, 
    const Rcpp::IntegerVector& predicted, 
    const Rcpp::NumericVector& w, 
    const int& estimator = 0, 
    const bool& na_rm = true) {
        
        fpr performance(actual, predicted, w, static_cast<metric::aggregate>(estimator), na_rm);
        return performance.compute();
}

//' @templateVar .FUN fpr
//' @templateVar .METHOD cmatrix
//' @template classification_standard_inherit
//'
//' @export
// [[Rcpp::export(fpr.cmatrix)]]
Rcpp::NumericVector cmatrix_false_positive_rate(
    const Rcpp::NumericMatrix& x, 
    const int& estimator = 0, 
    const bool& na_rm = true) {
        
        fpr performance(x, static_cast<metric::aggregate>(estimator), na_rm);
        return performance.compute();
}

//' @method fallout factor
//' @export
// [[Rcpp::export(fallout.factor)]]
Rcpp::NumericVector fallout(
    const Rcpp::IntegerVector& actual, 
    const Rcpp::IntegerVector& predicted, 
    const int& estimator = 0, 
    const bool& na_rm = true) {
        
        fpr performance(actual, predicted, static_cast<metric::aggregate>(estimator), na_rm);
        return performance.compute();
}

//' @method weighted.fallout factor
//' @export
// [[Rcpp::export(weighted.fallout.factor)]]
Rcpp::NumericVector weighted_fallout(
    const Rcpp::IntegerVector& actual, 
    const Rcpp::IntegerVector& predicted, 
    const Rcpp::NumericVector& w, 
    const int& estimator = 0, 
    const bool& na_rm = true) {

        fpr performance(actual, predicted, w, static_cast<metric::aggregate>(estimator), na_rm);
        return performance.compute();
}

//' @method fallout cmatrix
//' @export
// [[Rcpp::export(fallout.cmatrix)]]
Rcpp::NumericVector cmatrix_fallout(
    const Rcpp::NumericMatrix& x, 
    const int& estimator = 0, 
    const bool& na_rm = true) {

        fpr performance(x, static_cast<metric::aggregate>(estimator), na_rm);
        return performance.compute();
}
