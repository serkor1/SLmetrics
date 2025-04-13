#include <Rcpp.h>
#include "classification_FowlkesMallowsIndex.h"

using fowlkes_mallows_index_impl = metric::fowlkes_mallows_index<int>;

//' @templateVar .FUN fmi
//' @templateVar .METHOD factor
//' @template classification_standard_inherit
//'
//' @export
// [[Rcpp::export(fmi.factor)]]
double fowlkes_mallows_index(
    const Rcpp::IntegerVector& actual, 
    const Rcpp::IntegerVector& predicted) {

        fowlkes_mallows_index_impl performance(actual, predicted);
        return performance.compute();
}

//' @templateVar .FUN weighted.fmi
//' @templateVar .METHOD factor
//' @template classification_standard_inherit
//'
//' @export
// [[Rcpp::export(weighted.fmi.factor)]]
double weighted_fowlkes_mallows_index(
    const Rcpp::IntegerVector& actual, 
    const Rcpp::IntegerVector& predicted, 
    const Rcpp::NumericVector& w) {

        fowlkes_mallows_index_impl performance(actual, predicted, w);
        return performance.compute();
}

//' @templateVar .FUN fmi
//' @templateVar .METHOD cmatrix
//' @template classification_standard_inherit
//'
//' @export
// [[Rcpp::export(fmi.cmatrix)]]
double cmatrix_fowlkes_mallows_index(
    const Rcpp::NumericMatrix& x) {

        fowlkes_mallows_index_impl performance(x);
        return performance.compute();
}