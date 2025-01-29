#include <Rcpp.h>
#include "regression_CoefficientOfDetermination.h"
using namespace Rcpp;

//' @rdname rsq
//' @method rsq numeric
//' @export
// [[Rcpp::export(rsq.numeric)]]
double rsq(const Rcpp::NumericVector& actual,
           const Rcpp::NumericVector& predicted,
           double k = 0.0)
{
    // 1) Get pointers
    const double* ptrA = actual.begin();
    const double* ptrP = predicted.begin();
    std::size_t n = actual.size();

    // 2) Compute unweighted R^2 (or adjusted R^2 if k > 0)
    return CoefficientOfDetermination::compute(ptrA, ptrP, n, k);
}

//' @rdname rsq
//' @method weighted.rsq numeric
//' @export
// [[Rcpp::export(weighted.rsq.numeric)]]
double weighted_rsq(const Rcpp::NumericVector& actual,
                    const Rcpp::NumericVector& predicted,
                    const Rcpp::NumericVector& w,
                    double k = 0.0)
{
    // 1) Get pointers
    const double* ptrA = actual.begin();
    const double* ptrP = predicted.begin();
    const double* ptrW = w.begin();
    std::size_t n = actual.size();

    // 2) Compute weighted R^2 (or adjusted weighted R^2 if k > 0)
    return CoefficientOfDetermination::compute(ptrA, ptrP, ptrW, n, k);
}
