#include <Rcpp.h>
#include "regression_HuberLoss.h"
using namespace Rcpp;

//' @rdname huberloss
//' @method huberloss numeric
//' @export
// [[Rcpp::export(huberloss.numeric)]]
double huberloss(
    const Rcpp::NumericVector& actual, 
    const Rcpp::NumericVector& predicted, 
    double delta = 1.0) {

        metric::huberloss<double> performance(actual, predicted, delta);
        return performance.compute();

}

//' @rdname huberloss
//' @method weighted.huberloss numeric
//' @export
// [[Rcpp::export(weighted.huberloss.numeric)]]
double weighted_huberloss(
    const Rcpp::NumericVector& actual, 
    const Rcpp::NumericVector& predicted, 
    const Rcpp::NumericVector& w, 
    double delta = 1.0) {

        metric::weighted_huberloss<double> performance(actual, predicted, w, delta);
        return performance.compute();
}