#include <Rcpp.h>
#include "regression_ConcordanceCorrelationCoefficient.h"
using namespace Rcpp;

//' @rdname ccc
//' @method ccc numeric
//' @export
// [[Rcpp::export(ccc.numeric)]]
double ccc(const std::vector<double>& actual, const std::vector<double>& predicted, bool correction = false) 
{
    ConcordanceCorrelationCoefficient cccMetric(correction); // Instantiate CCC class
    return cccMetric.compute(actual, predicted);
}

//' @rdname ccc
//' @method weighted.ccc numeric
//' @export
// [[Rcpp::export(weighted.ccc.numeric)]]
double weighted_ccc(const std::vector<double>& actual, const std::vector<double>& predicted, const std::vector<double>& w, bool correction = false) 
{
    ConcordanceCorrelationCoefficient cccMetric(correction); // Instantiate CCC class
    return cccMetric.compute(actual, predicted, w);
}
