#include "regression_CoefficientOfDetermination.h"
#include <Rcpp.h>
using namespace Rcpp;

//' @rdname rsq
//' @method rsq numeric
//' @export
// [[Rcpp::export(rsq.numeric)]]
double rsq(const std::vector<double>& actual, const std::vector<double>& predicted, const double k = 0.0) 
{
    CoefficientOfDetermination rsqMetric(k); // Instantiate R-squared class
    return rsqMetric.compute(actual, predicted);
}

//' @rdname rsq
//' @method weighted.rsq numeric
//' @export
// [[Rcpp::export(weighted.rsq.numeric)]]
double weighted_rsq(const std::vector<double>& actual, const std::vector<double>& predicted, const std::vector<double>& w, const double k = 0.0) 
{
    CoefficientOfDetermination rsqMetric(k); // Instantiate R-squared class
    return rsqMetric.compute(actual, predicted, w);
}
