#include <Rcpp.h>
#include "regression_CoefficientOfDetermination.h"
using namespace Rcpp;

//' @rdname rsq
//' @method rsq numeric
//' @export
// [[Rcpp::export(rsq.numeric)]]
double rsq(
    const Rcpp::NumericVector& actual,
    const Rcpp::NumericVector& predicted,
    double k = 0.0) {

        metric::rsq<double> performance(actual, predicted, k);
        return performance.compute();
}

//' @rdname rsq
//' @method weighted.rsq numeric
//' @export
// [[Rcpp::export(weighted.rsq.numeric)]]
double weighted_rsq(
    const Rcpp::NumericVector& actual,
    const Rcpp::NumericVector& predicted,
    const Rcpp::NumericVector& w,
    double k = 0.0) {

        metric::weighted_rsq<double> performance(actual, predicted, w, k);
        return performance.compute();
}