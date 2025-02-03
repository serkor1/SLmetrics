#include <Rcpp.h>
#include "regression_RootRelativeSquaredError.h"
using namespace Rcpp;

//' @rdname rrse
//' @method rrse numeric
//' @export
// [[Rcpp::export(rrse.numeric)]]
double rrse(const Rcpp::NumericVector& actual, const Rcpp::NumericVector& predicted)
{
    // 1) Extract pointers and size
    const double* ptr_actual    = actual.begin();
    const double* ptr_predicted = predicted.begin();
    std::size_t n = actual.size();

    // 2) Compute unweighted RRSE
    return RRSE::compute(ptr_actual, ptr_predicted, n);
}

//' @rdname rrse
//' @method weighted.rrse numeric
//' @export
// [[Rcpp::export(weighted.rrse.numeric)]]
double weighted_rrse(const Rcpp::NumericVector& actual, const Rcpp::NumericVector& predicted, const Rcpp::NumericVector& w)
{
    // 1) Extract pointers and size
    const double* ptr_actual    = actual.begin();
    const double* ptr_predicted = predicted.begin();
    const double* ptr_w         = w.begin();
    std::size_t n = actual.size();

    // 2) Compute weighted RRSE
    return RRSE::compute(ptr_actual, ptr_predicted, ptr_w, n);
}
