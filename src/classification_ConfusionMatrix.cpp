#include "classification_ConfusionMatrix.h"

//' @templateVar .FUN cmatrix
//' @templateVar .METHOD factor
//' @template classification_standard_inherit
//'
//' @export
// [[Rcpp::export(cmatrix.factor)]]
Rcpp::NumericMatrix confusion_matrix(
    const Rcpp::IntegerVector& actual, 
    const Rcpp::IntegerVector& predicted) {

        metric::confusion_matrix<int> cmatrix(actual, predicted);
        return cmatrix.as_Rcpp();
}

//' @templateVar .FUN weighted.cmatrix
//' @templateVar .METHOD factor
//' @template classification_standard_inherit
//'
//' @export
// [[Rcpp::export(weighted.cmatrix.factor)]]
Rcpp::NumericMatrix weighted_confusion_matrix(
    const Rcpp::IntegerVector& actual, 
    const Rcpp::IntegerVector& predicted, 
    const Rcpp::NumericVector& w) {

        metric::confusion_matrix<int> cmatrix(actual, predicted, w);
        return cmatrix.as_Rcpp();
}
