#include <Rcpp.h>
#include "classification_DiagnosticOddsRatio.h"

// declare metric
using dor_impl = metric::diagnostic_odds_ratio<int>;

//' @rdname dor
//' @method dor factor
//' @export
// [[Rcpp::export(dor.factor)]]
Rcpp::NumericVector diagnostic_odds_ratio(
    const Rcpp::IntegerVector& actual, 
    const Rcpp::IntegerVector& predicted, 
    const int& estimator = 0, 
    bool na_rm = true) {
        
        dor_impl performance(actual, predicted, static_cast<metric::aggregate>(estimator), na_rm);
        return performance.compute();
}

//' @rdname dor
//' @method weighted.dor factor
//' @export
// [[Rcpp::export(weighted.dor.factor)]]
Rcpp::NumericVector weighted_diagnostic_odds_ratio(
    const Rcpp::IntegerVector& actual, 
    const Rcpp::IntegerVector& predicted, 
    const Rcpp::NumericVector& w, 
    const int& estimator = 0, 
    bool na_rm = true) {

        dor_impl performance(actual, predicted, w, static_cast<metric::aggregate>(estimator), na_rm);
        return performance.compute();
}

//' @rdname dor
//' @method dor cmatrix
//' @export
// [[Rcpp::export(dor.cmatrix)]]
Rcpp::NumericVector cmatrix_diagnostic_odds_ratio(
    const Rcpp::NumericMatrix& x,
    const int& estimator = 0,
    bool na_rm = true) {
        
        dor_impl performance(x, static_cast<metric::aggregate>(estimator), na_rm);
        return performance.compute();
}