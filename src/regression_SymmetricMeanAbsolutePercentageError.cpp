#include <Rcpp.h>
#include "regression_SymmetricMeanAbsolutePercentageError.h"
using namespace Rcpp;

//' @rdname smape
//' @method smape numeric
//' @export
// [[Rcpp::export(smape.numeric)]]
double smape(const std::vector<double>& actual, const std::vector<double>& predicted) 
{
    SymmetricMeanAbsolutePercentageError smapeMetric; // Instantiate SMAPE class
    return smapeMetric.compute(actual, predicted);
}

//' @rdname smape
//' @method weighted.smape numeric
//' @export
// [[Rcpp::export(weighted.smape.numeric)]]
double weighted_smape(const std::vector<double>& actual, const std::vector<double>& predicted, const std::vector<double>& w) 
{
    SymmetricMeanAbsolutePercentageError smapeMetric; // Instantiate SMAPE class
    return smapeMetric.compute(actual, predicted, w);
}
