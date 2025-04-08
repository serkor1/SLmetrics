#include <Rcpp.h>
#include "classification_NegativeLikelihoodRatio.h"

// declare metric
using nlr = metric::negative_likelihood_ratio<int>;

//' @rdname nlr
//' @method nlr factor
//' @export
// [[Rcpp::export(nlr.factor)]]
Rcpp::NumericVector negative_likelihood_ratio(
    const Rcpp::IntegerVector& actual, 
    const Rcpp::IntegerVector& predicted, 
    const int& estimator = 0, 
    bool na_rm = true) {
        
        nlr performance(actual, predicted, static_cast<metric::aggregate>(estimator), na_rm);
        return performance.compute();
}

//' @rdname nlr
//' @method weighted.nlr factor
//' @export
// [[Rcpp::export(weighted.nlr.factor)]]
Rcpp::NumericVector weighted_negative_likelihood_ratio(
    const Rcpp::IntegerVector& actual, 
    const Rcpp::IntegerVector& predicted, 
    const Rcpp::NumericVector& w, 
    const int& estimator = 0, 
    bool na_rm = true) {

        nlr performance(actual, predicted, w, static_cast<metric::aggregate>(estimator), na_rm);
        return performance.compute();
}

//' @rdname nlr
//' @method nlr cmatrix
//' @export
// [[Rcpp::export(nlr.cmatrix)]]
Rcpp::NumericVector cmatrix_negative_likelihood_ratio(
    const Rcpp::NumericMatrix& x,
    const int& estimator = 0,
    bool na_rm = true) {
        
        nlr performance(x, static_cast<metric::aggregate>(estimator), na_rm);
        return performance.compute();
}