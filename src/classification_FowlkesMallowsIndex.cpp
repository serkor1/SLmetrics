#include <Rcpp.h>
#include "classification_FowlkesMallowsIndex.h"

using fowlkes_mallows_index_impl = metric::fowlkes_mallows_index<int>;

//' @rdname fmi
//' @method fmi factor
//' @export
// [[Rcpp::export(fmi.factor)]]
double fowlkes_mallows_index(
    const Rcpp::IntegerVector& actual, 
    const Rcpp::IntegerVector& predicted) {

        fowlkes_mallows_index_impl performance(actual, predicted);
        return performance.compute();
}

//' @rdname fmi
//' @method weighted.fmi factor
//' @export
// [[Rcpp::export(weighted.fmi.factor)]]
double weighted_fowlkes_mallows_index(
    const Rcpp::IntegerVector& actual, 
    const Rcpp::IntegerVector& predicted, 
    const Rcpp::NumericVector& w) {

        fowlkes_mallows_index_impl performance(actual, predicted, w);
        return performance.compute();
}

//' @rdname fmi
//' @method fmi cmatrix
//' @export
// [[Rcpp::export(fmi.cmatrix)]]
double cmatrix_fowlkes_mallows_index(
    const Rcpp::NumericMatrix& x) {

        fowlkes_mallows_index_impl performance(x);
        return performance.compute();
}