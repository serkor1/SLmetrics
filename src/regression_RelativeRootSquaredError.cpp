#include <Rcpp.h>
#include "regression_RelativeRootSquaredError.h"
using namespace Rcpp;

//' @rdname rrse
//' @method rrse numeric
//' @export
// [[Rcpp::export(rrse.numeric)]]
double rrse(const std::vector<double>& actual, const std::vector<double>& predicted) 
{
    RelativeRootMeanSquaredError rrseMetric; // Instantiate RelativeRootMeanSquaredError class
    return rrseMetric.compute(actual, predicted);
}

//' @rdname rrse
//' @method weighted.rrse numeric
//' @export
// [[Rcpp::export(weighted.rrse.numeric)]]
double weighted_rrse(const std::vector<double>& actual, const std::vector<double>& predicted, const std::vector<double>& w) 
{
    RelativeRootMeanSquaredError rrseMetric; // Instantiate RelativeRootMeanSquaredError class
    return rrseMetric.compute(actual, predicted, w);
}
