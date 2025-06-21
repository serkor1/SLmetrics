#include "classification_Accuracy.h"

// implementation of metric
using accuracy_score_impl = metric::accuracy_score<int>;

//' @templateVar .FUN accuracy
//' @templateVar .METHOD factor
//' @template classification_standard_inherit
//'
//' @export
// [[Rcpp::export(accuracy.factor)]]
double accuracy(
    const Rcpp::IntegerVector& actual, 
    const Rcpp::IntegerVector& predicted) {

        accuracy_score_impl performance(actual, predicted);
        return performance.compute();
}

//' @templateVar .FUN weighted.accuracy
//' @templateVar .METHOD factor
//' @template classification_standard_inherit
//'
//' @export
// [[Rcpp::export(weighted.accuracy.factor)]]
double weighted_accuracy(
    const Rcpp::IntegerVector& actual, 
    const Rcpp::IntegerVector& predicted, 
    const Rcpp::NumericVector& w) {

        accuracy_score_impl performance(actual, predicted, w);
        return performance.compute();
}

//' @templateVar .FUN accuracy
//' @templateVar .METHOD cmatrix
//' @template classification_standard_inherit
//'
//' @export
// [[Rcpp::export(accuracy.cmatrix)]]
double cmatrix_accuracy(
    const Rcpp::NumericMatrix& x) {

        accuracy_score_impl performance(x);
        return performance.compute();
}
