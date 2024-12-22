#include <Rcpp.h>
#include "regression_MeanSquaredError.h"
using namespace Rcpp;

//' @rdname mse
//' @method mse numeric
//' @export
// [[Rcpp::export(mse.numeric)]]
double mse(const std::vector<double>& actual, const std::vector<double>& predicted) 
{
    MeanSquaredError mseMetric; // Instantiate MSE class
    return mseMetric.compute(actual, predicted);
}

//' @rdname mse
//' @method weighted.mse numeric
//' @export
// [[Rcpp::export(weighted.mse.numeric)]]
double weighted_mse(const std::vector<double>& actual, const std::vector<double>& predicted, const std::vector<double>& w) 
{
    MeanSquaredError mseMetric; // Instantiate MSE class
    return mseMetric.compute(actual, predicted, w);
}
