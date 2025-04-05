#include <Rcpp.h>
#include "regression_PinballLoss.h"
using namespace Rcpp;

//' @rdname pinball
//' @method pinball numeric
//' @export
// [[Rcpp::export(pinball.numeric)]]
double pinball(
    const Rcpp::NumericVector& actual,
    const Rcpp::NumericVector& predicted,
    double alpha = 0.5,
    bool deviance = false) {

        metric::pinball_loss<double> performance(actual, predicted, alpha, deviance);
        return performance.compute();
}

//' @rdname pinball
//' @method weighted.pinball numeric
//' @export
// [[Rcpp::export(weighted.pinball.numeric)]]
double weighted_pinball(
    const Rcpp::NumericVector& actual,
    const Rcpp::NumericVector& predicted,
    const Rcpp::NumericVector& w,
    double alpha = 0.5,
    bool deviance = false) {

        metric::weighted_pinball_loss<double> performance(actual, predicted, w, alpha, deviance);
        return performance.compute();
}
