#include <Rcpp.h>
#include "regression_RelativeAbsoluteError.h"
using namespace Rcpp;

//' @rdname rae
//' @method rae numeric
//' @export
// [[Rcpp::export(rae.numeric)]]
double rae(const Rcpp::NumericVector& actual, const Rcpp::NumericVector& predicted)
{
    // 1) Extract pointers and size
    const double* ptr_actual    = actual.begin();
    const double* ptr_predicted = predicted.begin();
    std::size_t n = actual.size();

    // 2) Unweighted RAE
    return RAE::compute(ptr_actual, ptr_predicted, n);
}

//' @rdname rae
//' @method weighted.rae numeric
//' @export
// [[Rcpp::export(weighted.rae.numeric)]]
double weighted_rae(const Rcpp::NumericVector& actual, const Rcpp::NumericVector& predicted, const Rcpp::NumericVector& w)
{
    // 1) Extract pointers and size
    const double* ptr_actual    = actual.begin();
    const double* ptr_predicted = predicted.begin();
    const double* ptr_w         = w.begin();
    std::size_t n = actual.size();

    // 2) Weighted RAE
    return RAE::compute(ptr_actual, ptr_predicted, ptr_w, n);
}
