#include <Rcpp.h>
#include "regression_ConcordanceCorrelationCoefficient.h"
using namespace Rcpp;

//' @rdname ccc
//' @method ccc numeric
//' @export
// [[Rcpp::export(ccc.numeric)]]
double ccc(const Rcpp::NumericVector& actual,
           const Rcpp::NumericVector& predicted,
           bool correction = false)
{
    const double* ptrA = actual.begin();
    const double* ptrP = predicted.begin();
    std::size_t n = actual.size();

    return CCC::compute(ptrA, ptrP, n, correction);
}

//' @rdname ccc
//' @method weighted.ccc numeric
//' @export
// [[Rcpp::export(weighted.ccc.numeric)]]
double weighted_ccc(const Rcpp::NumericVector& actual,
                    const Rcpp::NumericVector& predicted,
                    const Rcpp::NumericVector& w,
                    bool correction = false)
{
    const double* ptrA = actual.begin();
    const double* ptrP = predicted.begin();
    const double* ptrW = w.begin();
    std::size_t n = actual.size();

    return CCC::compute(ptrA, ptrP, ptrW, n, correction);
}
