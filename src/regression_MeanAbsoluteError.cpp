#include <Rcpp.h>
#include "regression_MeanAbsoluteError.h"
using namespace Rcpp;

//' @rdname mae
//' @method mae numeric
//' @export
// [[Rcpp::export(mae.numeric)]]
double mae(const std::vector<double>& actual, const std::vector<double>& predicted) 
{
    MeanAbsoluteError maeMetric; // Instantiate MAE class
    return maeMetric.compute(actual, predicted);
}

//' @rdname mae
//' @method weighted.mae numeric
//' @export
// [[Rcpp::export(weighted.mae.numeric)]]
double weighted_mae(const std::vector<double>& actual, const std::vector<double>& predicted, const std::vector<double>& w) 
{
    MeanAbsoluteError maeMetric; // Instantiate MAE class
    return maeMetric.compute(actual, predicted, w);
}
