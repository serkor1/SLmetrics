#include <Rcpp.h>
#include "regression_RootMeanSquaredLogarithmicError.h"
using namespace Rcpp;

//' @rdname rmsle
//' @method rmsle numeric
//' @export
// [[Rcpp::export(rmsle.numeric)]]
double rmsle(const NumericVector& actual, const NumericVector& predicted)
{
    const double* ptr_actual    = actual.begin();
    const double* ptr_predicted = predicted.begin();
    std::size_t n = actual.size();

    return RMSLE::compute(ptr_actual, ptr_predicted, n);
}

//' @rdname rmsle
//' @method weighted.rmsle numeric
//' @export
// [[Rcpp::export(weighted.rmsle.numeric)]]
double weighted_rmsle(const NumericVector& actual, 
                      const NumericVector& predicted, 
                      const NumericVector& w)
{
    const double* ptr_actual    = actual.begin();
    const double* ptr_predicted = predicted.begin();
    const double* ptr_w         = w.begin();
    std::size_t n = actual.size();

    return RMSLE::compute(ptr_actual, ptr_predicted, ptr_w, n);
}
