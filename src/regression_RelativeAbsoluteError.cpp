#include <Rcpp.h>
#include "regression_RelativeAbsoluteError.h"
using namespace Rcpp;

//' @rdname rae
//' @method rae numeric
//' @export
// [[Rcpp::export(rae.numeric)]]
double rae(const std::vector<double>& actual, const std::vector<double>& predicted) 
{
    RelativeAbsoluteError raeMetric; // Instantiate RelativeAbsoluteError class
    return raeMetric.compute(actual, predicted);
}

//' @rdname rae
//' @method weighted.rae numeric
//' @export
// [[Rcpp::export(weighted.rae.numeric)]]
double weighted_rae(const std::vector<double>& actual, const std::vector<double>& predicted, const std::vector<double>& w) 
{
    RelativeAbsoluteError raeMetric; // Instantiate RelativeAbsoluteError class
    return raeMetric.compute(actual, predicted, w);
}
