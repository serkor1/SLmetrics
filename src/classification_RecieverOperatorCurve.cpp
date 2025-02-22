#include "classification_RecieverOperatorCurve.h"
#include <Rcpp.h>
using namespace Rcpp;



//' @rdname ROC
//' @method ROC factor
//' @export
// [[Rcpp::export(ROC.factor)]]
Rcpp::DataFrame RecieverOperatorCharacteristics(const Rcpp::IntegerVector& actual, const Rcpp::NumericVector& response, Rcpp::Nullable<Rcpp::NumericVector> thresholds = R_NilValue) {
    ROCCalculator roc_calculator(actual, response, thresholds);
    return roc_calculator.calculate();
}

//' @rdname ROC
//' @method weighted.ROC factor
//' @export
// [[Rcpp::export(weighted.ROC.factor)]]
Rcpp::DataFrame weighted_RecieverOperatorCharacteristics(const Rcpp::IntegerVector& actual, const Rcpp::NumericVector& response, const Rcpp::NumericVector& w, Rcpp::Nullable<Rcpp::NumericVector> thresholds = R_NilValue) {
    ROCCalculator roc_calculator(actual, response, w, thresholds);
    return roc_calculator.calculate();
}