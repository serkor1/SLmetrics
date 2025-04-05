#include "SLmetrics.h"

using namespace Rcpp;

//' @rdname cmatrix
//' @method cmatrix factor
//' @export
// [[Rcpp::export(cmatrix.factor)]]
Rcpp::NumericMatrix confusion_matrix(
    const Rcpp::IntegerVector& actual, 
    const Rcpp::IntegerVector& predicted) {

        classification::confusion_matrix<int> cmatrix(actual, predicted);
        return cmatrix.construct_matrix();
}

//' @rdname cmatrix
//' @method weighted.cmatrix factor
//' @export
// [[Rcpp::export(weighted.cmatrix.factor)]]
Rcpp::NumericMatrix weighted_confusion_matrix(
    const Rcpp::IntegerVector& actual, 
    const Rcpp::IntegerVector& predicted, 
    const Rcpp::NumericVector& w) {

        classification::confusion_matrix<int> cmatrix(actual, predicted);
        return cmatrix.construct_matrix(w);
}
