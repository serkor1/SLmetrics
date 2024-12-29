#include "classification_PrecisionRecallCurve.h"
#include <Rcpp.h>
using namespace Rcpp;


//' @rdname prROC
//' @method prROC factor
//' @export
// [[Rcpp::export(prROC.factor)]]
Rcpp::DataFrame PrecisionRecallCurve(const Rcpp::IntegerVector& actual, const Rcpp::NumericVector& response, Rcpp::Nullable<Rcpp::NumericVector> thresholds = R_NilValue) {
    PRCalculator pr_calculator(actual, response, thresholds);
    return pr_calculator.calculate();
}

//' @rdname prROC
//' @method weighted.prROC factor
//' @export
// [[Rcpp::export(weighted.prROC.factor)]]
Rcpp::DataFrame weighted_PrecisionRecallCurve(const Rcpp::IntegerVector& actual, const Rcpp::NumericVector& response, const Rcpp::NumericVector& w, Rcpp::Nullable<Rcpp::NumericVector> thresholds = R_NilValue) {
    PRCalculator pr_calculator(actual, response, w, thresholds);
    return pr_calculator.calculate();
}