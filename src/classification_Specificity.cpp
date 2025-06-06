#include <Rcpp.h>
#include "classification_Specificity.h"

// declare metric
using specificity_score_impl = metric::specificity<int>;

//' @templateVar .FUN specificity
//' @templateVar .METHOD factor
//' @template classification_standard_inherit
//'
//' @export
// [[Rcpp::export(specificity.factor)]]
Rcpp::NumericVector specificity(
    const Rcpp::IntegerVector& actual, 
    const Rcpp::IntegerVector& predicted, 
    const int& estimator = 0, 
    bool na_rm = true) {
        
        specificity_score_impl performance(actual, predicted, static_cast<metric::aggregate>(estimator), na_rm);
        return performance.compute();
}

//' @templateVar .FUN weighted.specificity
//' @templateVar .METHOD factor
//' @template classification_standard_inherit
//'
//' @export
// [[Rcpp::export(weighted.specificity.factor)]]
Rcpp::NumericVector weighted_specificity(
    const Rcpp::IntegerVector& actual, 
    const Rcpp::IntegerVector& predicted, 
    const Rcpp::NumericVector& w, 
    const int& estimator = 0, 
    bool na_rm = true) {

        specificity_score_impl performance(actual, predicted, w, static_cast<metric::aggregate>(estimator), na_rm);
        return performance.compute();
}

//' @templateVar .FUN specificity
//' @templateVar .METHOD cmatrix
//' @template classification_standard_inherit
//'
//' @export
// [[Rcpp::export(specificity.cmatrix)]]
Rcpp::NumericVector cmatrix_specificity(
    const Rcpp::NumericMatrix& x,
    const int& estimator = 0,
    bool na_rm = true) {
        
        specificity_score_impl performance(x, static_cast<metric::aggregate>(estimator), na_rm);
        return performance.compute();
}

//' @method tnr factor
//' @export
// [[Rcpp::export(tnr.factor)]]
Rcpp::NumericVector true_negative_rate(
    const Rcpp::IntegerVector& actual, 
    const Rcpp::IntegerVector& predicted, 
    const int& estimator = 0, 
    bool na_rm = true) {
        
        specificity_score_impl performance(actual, predicted, static_cast<metric::aggregate>(estimator), na_rm);
        return performance.compute();
}

//' @method weighted.tnr factor
//' @export
// [[Rcpp::export(weighted.tnr.factor)]]
Rcpp::NumericVector weighted_true_negative_rate(
    const Rcpp::IntegerVector& actual, 
    const Rcpp::IntegerVector& predicted, 
    const Rcpp::NumericVector& w, 
    const int& estimator = 0, 
    bool na_rm = true) {

        specificity_score_impl performance(actual, predicted, w, static_cast<metric::aggregate>(estimator), na_rm);
        return performance.compute();
}

//' @method tnr cmatrix
//' @export
// [[Rcpp::export(tnr.cmatrix)]]
Rcpp::NumericVector cmatrix_true_negative_rate(
    const Rcpp::NumericMatrix& x,
    const int& estimator = 0,
    bool na_rm = true) {
        
        specificity_score_impl performance(x, static_cast<metric::aggregate>(estimator), na_rm);
        return performance.compute();
}

//' @method selectivity factor
//' @export
// [[Rcpp::export(selectivity.factor)]]
Rcpp::NumericVector selectivity(
    const Rcpp::IntegerVector& actual, 
    const Rcpp::IntegerVector& predicted, 
    const int& estimator = 0, 
    bool na_rm = true) {
        
        specificity_score_impl performance(actual, predicted, static_cast<metric::aggregate>(estimator), na_rm);
        return performance.compute();
}

//' @method weighted.selectivity factor
//' @export
// [[Rcpp::export(weighted.selectivity.factor)]]
Rcpp::NumericVector weighted_selectivity(
    const Rcpp::IntegerVector& actual, 
    const Rcpp::IntegerVector& predicted, 
    const Rcpp::NumericVector& w, 
    const int& estimator = 0, 
    bool na_rm = true) {

        specificity_score_impl performance(actual, predicted, w, static_cast<metric::aggregate>(estimator), na_rm);
        return performance.compute();
}

//' @method selectivity cmatrix
//' @export
// [[Rcpp::export(selectivity.cmatrix)]]
Rcpp::NumericVector cmatrix_selectivity(
    const Rcpp::NumericMatrix& x,
    const int& estimator = 0,
    bool na_rm = true) {
        
        specificity_score_impl performance(x, static_cast<metric::aggregate>(estimator), na_rm);
        return performance.compute();
}