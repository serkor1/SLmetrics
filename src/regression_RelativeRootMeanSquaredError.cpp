#include <Rcpp.h>
#include "regression_RelativeRootMeanSquaredError.h"

using namespace Rcpp;

//' @rdname rrmse
//' @method rrmse numeric
//' @export
// [[Rcpp::export(rrmse.numeric)]]
double RelativeRootMeanSquaredError(const Rcpp::NumericVector& actual, const Rcpp::NumericVector& predicted, const int normalization = 1)
{
    // 1) Extract pointers
    const double* ptr_actual    = actual.begin();
    const double* ptr_predicted = predicted.begin();

    // 2) Determine size
    std::size_t n = actual.size();

    // 3) Compute RRMSE (unweighted)
    return RRMSE::compute(ptr_actual, ptr_predicted, n, normalization);
}

//' @rdname rrmse
//' @method weighted.rrmse numeric
//' @export
// [[Rcpp::export(weighted.rrmse.numeric)]]
double weighted_RelativeRootMeanSquaredError(const Rcpp::NumericVector& actual, const Rcpp::NumericVector& predicted, const Rcpp::NumericVector& w, const int normalization = 1)
{
    // 1) Extract pointers
    const double* ptr_actual    = actual.begin();
    const double* ptr_predicted = predicted.begin();
    const double* ptr_w         = w.begin();

    // 2) Determine size
    std::size_t n = actual.size();

    // 3) Compute RRMSE (weighted)
    return RRMSE::compute(ptr_actual, ptr_predicted, ptr_w, n, normalization);
}