#include <Rcpp.h>
#include "regression_RootMeanSquaredLogarithmicError.h"
using namespace Rcpp;

//' @rdname rmsle
//' @method rmsle numeric
//' @export
// [[Rcpp::export(rmsle.numeric)]]
double rmsle(const std::vector<double>& actual, const std::vector<double>& predicted) 
{
    RootMeanSquaredLogarithmicError rmsleMetric; // Instantiate RootMeanSquaredLogarithmicError class
    return rmsleMetric.compute(actual, predicted);
}

//' @rdname rmsle
//' @method weighted.rmsle numeric
//' @export
// [[Rcpp::export(weighted.rmsle.numeric)]]
double weighted_rmsle(const std::vector<double>& actual, const std::vector<double>& predicted, const std::vector<double>& w) 
{
    RootMeanSquaredLogarithmicError rmsleMetric; // Instantiate RootMeanSquaredLogarithmicError class
    return rmsleMetric.compute(actual, predicted, w);
}
