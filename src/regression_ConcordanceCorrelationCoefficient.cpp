#include <Rcpp.h>
#include "regression_ConcordanceCorrelationCoefficient.h"
using namespace Rcpp;

//' @rdname ccc
//' @method ccc numeric
//' @export
// [[Rcpp::export(ccc.numeric)]]
double ccc(
    const Rcpp::NumericVector& actual,
    const Rcpp::NumericVector& predicted,
    bool correction = false) {

        metric::CCC<double> performance(actual, predicted, correction);
        return performance.compute();
}

//' @rdname ccc
//' @method weighted.ccc numeric
//' @export
// [[Rcpp::export(weighted.ccc.numeric)]]
double weighted_ccc(
    const Rcpp::NumericVector& actual,
    const Rcpp::NumericVector& predicted,
    const Rcpp::NumericVector& w,
    bool correction = false) {

        metric::weighted_CCC<double> performance(actual, predicted, w, correction);
        return performance.compute();
}
