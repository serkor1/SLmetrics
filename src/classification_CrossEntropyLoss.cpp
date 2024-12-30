#include <Rcpp.h>
#include "classification_CrossEntropyLoss.h"
using namespace Rcpp;

//' @rdname entropy
//' @method entropy factor
//' @export
// [[Rcpp::export(entropy.factor)]]
double CrossEntropy(const IntegerVector& actual, const NumericMatrix& response, const bool normalize = true)
{
    CrossEntropyClass CrossEntropyMetric(normalize);
    return CrossEntropyMetric.compute(actual, response);
}

//' @rdname weighted.entropy
//' @method weighted.entropy factor
//' @export
// [[Rcpp::export(weighted.entropy.factor)]]
double weighted_CrossEntropy(const IntegerVector& actual, const NumericMatrix& response, const NumericVector& w, const bool normalize = true)
{
    CrossEntropyClass CrossEntropyMetric(normalize);
    return CrossEntropyMetric.compute(actual, response, w);
}

//' @rdname entropy
//' @method logloss factor
//' @export
// [[Rcpp::export(logloss.factor)]]
double LogLoss(const IntegerVector& actual, const NumericMatrix& response, const bool normalize = true)
{
    CrossEntropyClass CrossEntropyMetric(normalize);
    return CrossEntropyMetric.compute(actual, response);
}

//' @rdname weighted.entropy
//' @method weighted.logloss factor
//' @export
// [[Rcpp::export(weighted.logloss.factor)]]
double weighted_LogLoss(const IntegerVector& actual, const NumericMatrix& response, const NumericVector& w, const bool normalize = true)
{
    CrossEntropyClass CrossEntropyMetric(normalize);
    return CrossEntropyMetric.compute(actual, response, w);
}

