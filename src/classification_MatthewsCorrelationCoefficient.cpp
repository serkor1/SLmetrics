#include "classification_MatthewsCorrelationCoefficient.h"

// implementation of metric
using mcc_score_impl = metric::matthews_correlation_coefficient<int>;

//' @templateVar .FUN mcc
//' @templateVar .METHOD factor
//' @template classification_standard_inherit
//'
//' @export
// [[Rcpp::export(mcc.factor)]]
double mcc(
    const Rcpp::IntegerVector& actual, 
    const Rcpp::IntegerVector& predicted) {

        mcc_score_impl performance(actual, predicted);
        return performance.compute();
}

//' @templateVar .FUN weighted.mcc
//' @templateVar .METHOD factor
//' @template classification_standard_inherit
//'
//' @export
// [[Rcpp::export(weighted.mcc.factor)]]
double weighted_mcc(
    const Rcpp::IntegerVector& actual, 
    const Rcpp::IntegerVector& predicted, 
    const Rcpp::NumericVector& w) {

        mcc_score_impl performance(actual, predicted, w);
        return performance.compute();
}

//' @templateVar .FUN mcc
//' @templateVar .METHOD cmatrix
//' @template classification_standard_inherit
//'
//' @export
// [[Rcpp::export(mcc.cmatrix)]]
double cmatrix_mcc(
    const Rcpp::NumericMatrix& x) {

        mcc_score_impl performance(x);
        return performance.compute();
}

//' @method phi factor
//' @export
// [[Rcpp::export(phi.factor)]]
double phi_coefficient(
    const Rcpp::IntegerVector& actual, 
    const Rcpp::IntegerVector& predicted) {

        mcc_score_impl performance(actual, predicted);
        return performance.compute();
}

//' @method weighted.phi factor
//' @export
// [[Rcpp::export(weighted.phi.factor)]]
double weighted_phi_coefficient(
    const Rcpp::IntegerVector& actual, 
    const Rcpp::IntegerVector& predicted, 
    const Rcpp::NumericVector& w) {

        mcc_score_impl performance(actual, predicted, w);
        return performance.compute();
}

//' @method phi cmatrix
//' @export
// [[Rcpp::export(phi.cmatrix)]]
double cmatrix_phi_coefficient(
    const Rcpp::NumericMatrix& x) {

        mcc_score_impl performance(x);
        return performance.compute();
}