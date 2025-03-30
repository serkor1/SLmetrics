#include <Rcpp.h>
#include "regression_MeanPercentageError.h"
using namespace Rcpp;

//' @rdname mpe
//' @method mpe numeric
//' @export
// [[Rcpp::export(mpe.numeric)]]
double mpe(
    const Rcpp::NumericVector& actual,
    const Rcpp::NumericVector& predicted) {

        metric::MPE<double> performance(actual, predicted);
        return performance.compute();
}

//' @rdname mpe
//' @method weighted.mpe numeric
//' @export
// [[Rcpp::export(weighted.mpe.numeric)]]
double weighted_mpe(
    const Rcpp::NumericVector& actual,
    const Rcpp::NumericVector& predicted,
    const Rcpp::NumericVector& w) {

        metric::weighted_MPE<double> performance(actual, predicted, w);
        return performance.compute();
}
