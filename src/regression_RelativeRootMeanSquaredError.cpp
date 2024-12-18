#include <Rcpp.h>
#include "regression_RelativeRootMeanSquaredError.h"
using namespace Rcpp;

//' @rdname rrmse
//' @method rrmse numeric
//' @export
// [[Rcpp::export(rrmse.numeric)]]
double rrmse(const std::vector<double>& actual, const std::vector<double>& predicted) 
{
    RelativeRootMeanSquaredError rrmseMetric; // Instantiate RelativeRootMeanSquaredError class
    return rrmseMetric.compute(actual, predicted);
}

//' @rdname rrmse
//' @method weighted.rrmse numeric
//' @export
// [[Rcpp::export(weighted.rrmse.numeric)]]
double weighted_rrmse(const std::vector<double>& actual, const std::vector<double>& predicted, const std::vector<double>& w) 
{
    RelativeRootMeanSquaredError rrmseMetric; // Instantiate RelativeRootMeanSquaredError class
    return rrmseMetric.compute(actual, predicted, w);
}
