#include <Rcpp.h>
#include "regression_MeanPercentageError.h"
using namespace Rcpp;

//' @rdname mpe
//' @method mpe numeric
//' @export
// [[Rcpp::export(mpe.numeric)]]
double mpe(const std::vector<double>& actual, const std::vector<double>& predicted) 
{
    MeanPercentageError mpeMetric; // Instantiate MPE class
    return mpeMetric.compute(actual, predicted);
}

//' @rdname mpe
//' @method weighted.mpe numeric
//' @export
// [[Rcpp::export(weighted.mpe.numeric)]]
double weighted_mpe(const std::vector<double>& actual, const std::vector<double>& predicted, const std::vector<double>& w) 
{
    MeanPercentageError mpeMetric; // Instantiate MPE class
    return mpeMetric.compute(actual, predicted, w);
}
