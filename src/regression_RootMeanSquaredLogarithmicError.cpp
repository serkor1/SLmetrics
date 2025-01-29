#include <Rcpp.h>
#include "regression_RootMeanSquaredLogarithmicError.h"
using namespace Rcpp;

//' @rdname rmsle
//' @method rmsle numeric
//' @export
// [[Rcpp::export(rmsle.numeric)]]
double rmsle(const Rcpp::NumericVector& actual, const Rcpp::NumericVector& predicted)
{
    // 1) extract pointers to 
    // to data, and size
    const double* ptr_actual    = actual.begin();
    const double* ptr_predicted = predicted.begin();
    std::size_t n = actual.size();

    // 2) calculate and
    // return value
    return RMSLE::compute(ptr_actual, ptr_predicted, n);
}

//' @rdname rmsle
//' @method weighted.rmsle numeric
//' @export
// [[Rcpp::export(weighted.rmsle.numeric)]]
double weighted_rmsle(const Rcpp::NumericVector& actual, const Rcpp::NumericVector& predicted, const Rcpp::NumericVector& w)
{
    // 1) extract pointers to 
    // to data, and size
    const double* ptr_actual    = actual.begin();
    const double* ptr_predicted = predicted.begin();
    const double* ptr_w         = w.begin();
    std::size_t n = actual.size();

    // 2) calculate and
    // return value
    return RMSLE::compute(ptr_actual, ptr_predicted, ptr_w, n);
}
