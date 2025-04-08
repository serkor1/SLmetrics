#include <Rcpp.h>
#include "classification_PositiveLikelihoodRatio.h"

// declare metric
using plr = metric::positive_likelihood_ratio<int>;

//' @rdname plr
//' @method plr factor
//' @export
// [[Rcpp::export(plr.factor)]]
Rcpp::NumericVector positive_likelihood_ratio(
    const Rcpp::IntegerVector& actual, 
    const Rcpp::IntegerVector& predicted, 
    const int& estimator = 0, 
    bool na_rm = true) {
        
        plr performance(actual, predicted, static_cast<metric::aggregate>(estimator), na_rm);
        return performance.compute();
}

//' @rdname plr
//' @method weighted.plr factor
//' @export
// [[Rcpp::export(weighted.plr.factor)]]
Rcpp::NumericVector weighted_positive_likelihood_ratio(
    const Rcpp::IntegerVector& actual, 
    const Rcpp::IntegerVector& predicted, 
    const Rcpp::NumericVector& w, 
    const int& estimator = 0, 
    bool na_rm = true) {

        plr performance(actual, predicted, w, static_cast<metric::aggregate>(estimator), na_rm);
        return performance.compute();
}

//' @rdname plr
//' @method plr cmatrix
//' @export
// [[Rcpp::export(plr.cmatrix)]]
Rcpp::NumericVector cmatrix_positive_likelihood_ratio(
    const Rcpp::NumericMatrix& x,
    const int& estimator = 0,
    bool na_rm = true) {
        
        plr performance(x, static_cast<metric::aggregate>(estimator), na_rm);
        return performance.compute();
}