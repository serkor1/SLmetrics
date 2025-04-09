#include <Rcpp.h>
#include "classification_NegativeLikelihoodRatio.h"

// declare metric
using negative_likelihood_ratio_impl = metric::negative_likelihood_ratio<int>;

//' @rdname nlr
//' @method nlr factor
//' @export
// [[Rcpp::export(nlr.factor)]]
double negative_likelihood_ratio(
    const Rcpp::IntegerVector& actual,
    const Rcpp::IntegerVector& predicted) {

        negative_likelihood_ratio_impl performance(actual, predicted);
        return performance.compute();
}

//' @rdname nlr
//' @method weighted.nlr factor
//' @export
// [[Rcpp::export(weighted.nlr.factor)]]
double weighted_negative_likelihood_ratio(
    const Rcpp::IntegerVector& actual,
    const Rcpp::IntegerVector& predicted,
    const Rcpp::NumericVector& w) {

        negative_likelihood_ratio_impl performance(actual, predicted, w);
        return performance.compute();
}

//' @rdname nlr
//' @method nlr cmatrix
//' @export
// [[Rcpp::export(nlr.cmatrix)]]
double cmatrix_negative_likelihood_ratio(
    const Rcpp::NumericMatrix& x) {

        negative_likelihood_ratio_impl performance(x);
        return performance.compute();
}
