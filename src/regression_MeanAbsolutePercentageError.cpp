#include <Rcpp.h>
#include "regression_MeanAbsolutePercentageError.h"
using namespace Rcpp;

//' @rdname mape
//' @method mape numeric
//' @export
// [[Rcpp::export(mape.numeric)]]
double mape(const std::vector<double>& actual, const std::vector<double>& predicted) 
{
    MeanAbsolutePercentageError mapeMetric; // Instantiate MAPE class
    return mapeMetric.compute(actual, predicted);
}

//' @rdname mape
//' @method weighted.mape numeric
//' @export
// [[Rcpp::export(weighted.mape.numeric)]]
double weighted_mape(const std::vector<double>& actual, const std::vector<double>& predicted, const std::vector<double>& w) 
{
    MeanAbsolutePercentageError mapeMetric; // Instantiate MAPE class
    return mapeMetric.compute(actual, predicted, w);
}
