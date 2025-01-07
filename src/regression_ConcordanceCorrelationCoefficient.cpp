#include <Rcpp.h>
#include "regression_ConcordanceCorrelationCoefficient.h"
using namespace Rcpp;

//' @rdname ccc
//' @method ccc numeric
//' @export
// [[Rcpp::export(ccc.numeric)]]
double ccc(const std::vector<double>& actual, const std::vector<double>& predicted, bool correction = false) 
{
    return ConcordanceCorrelationCalculator::computeUnweighted(
        actual, predicted, correction
    );
}

//' @rdname ccc
//' @method weighted.ccc numeric
//' @export
// [[Rcpp::export(weighted.ccc.numeric)]]
double weighted_ccc(const std::vector<double>& actual, const std::vector<double>& predicted, const std::vector<double>& w, bool correction = false) 
{
     return ConcordanceCorrelationCalculator::computeWeighted(
        actual, predicted, w, correction
    );
}
