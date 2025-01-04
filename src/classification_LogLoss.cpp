#include <Rcpp.h>
#include "classification_LogLoss.h"
using namespace Rcpp;

//' @rdname logloss
//' @method logloss factor
//' @export
// [[Rcpp::export(logloss.factor)]]
double LogLoss(const IntegerVector& actual, const NumericMatrix& qk, const bool normalize = true)
{
    LogLossClass LogLossMetric(normalize);
    return LogLossMetric.compute(actual, qk);
}

//' @rdname logloss
//' @method weighted.logloss factor
//' @export
// [[Rcpp::export(weighted.logloss.factor)]]
double weighted_LogLoss(const IntegerVector& actual, const NumericMatrix& qk, const NumericVector& w, const bool normalize = true)
{
    LogLossClass LogLossMetric(normalize);
    return LogLossMetric.compute(actual, qk, w);
}

