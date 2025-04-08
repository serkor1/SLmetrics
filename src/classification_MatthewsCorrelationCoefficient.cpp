#include <Rcpp.h>
#include "classification_MatthewsCorrelationCoefficient.h"

// implementation of metric
using mcc_score_impl = metric::matthews_correlation_coefficient<int>;

//' @rdname mcc
//' @method mcc factor
//' @export
// [[Rcpp::export(mcc.factor)]]
double mcc(
    const Rcpp::IntegerVector& actual, 
    const Rcpp::IntegerVector& predicted) {

        mcc_score_impl performance(actual, predicted);
        return performance.compute();
}

//' @rdname mcc
//' @method weighted.mcc factor
//' @export
// [[Rcpp::export(weighted.mcc.factor)]]
double weighted_mcc(
    const Rcpp::IntegerVector& actual, 
    const Rcpp::IntegerVector& predicted, 
    const Rcpp::NumericVector& w) {

        mcc_score_impl performance(actual, predicted, w);
        return performance.compute();
}

//' @rdname mcc
//' @method mcc cmatrix
//' @export
// [[Rcpp::export(mcc.cmatrix)]]
double cmatrix_mcc(
    const Rcpp::NumericMatrix& x) {

        mcc_score_impl performance(x);
        return performance.compute();
}

//' @rdname mcc
//' @method phi factor
//' @export
// [[Rcpp::export(phi.factor)]]
double phi_coefficient(
    const Rcpp::IntegerVector& actual, 
    const Rcpp::IntegerVector& predicted) {

        mcc_score_impl performance(actual, predicted);
        return performance.compute();
}

//' @rdname mcc
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

//' @rdname mcc
//' @method phi cmatrix
//' @export
// [[Rcpp::export(phi.cmatrix)]]
double cmatrix_phi_coefficient(
    const Rcpp::NumericMatrix& x) {

        mcc_score_impl performance(x);
        return performance.compute();
}