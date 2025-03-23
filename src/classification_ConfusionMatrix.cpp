// [[Rcpp::depends(RcppEigen)]]
#include <RcppEigen.h>
#include "classification_ConfusionMatrix.h"
#include <Rcpp.h>
#include <memory>

using namespace Rcpp;

//' @rdname cmatrix
//' @method cmatrix factor
//' @export
// [[Rcpp::export(cmatrix.factor)]]
Rcpp::NumericMatrix confusion_matrix(
    const Rcpp::IntegerVector& actual, 
    const Rcpp::IntegerVector& predicted) {

        auto args = std::make_unique<ConfusionMatrixClass>(actual, predicted);
        return args -> construct_matrix();

}

//' @rdname cmatrix
//' @method weighted.cmatrix factor
//' @export
// [[Rcpp::export(weighted.cmatrix.factor)]]
Rcpp::NumericMatrix weighted_confusion_matrix(
    const Rcpp::IntegerVector& actual, 
    const Rcpp::IntegerVector& predicted, 
    const Rcpp::NumericVector& w) {

        auto args = std::make_unique<ConfusionMatrixClass>(actual, predicted);
        return args->construct_matrix(w);

}
