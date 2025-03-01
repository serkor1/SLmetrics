#include <Rcpp.h>
#include "regression_MeanSquaredError.h"
using namespace Rcpp;

//' @rdname mse
//' @method mse numeric
//' @export
// [[Rcpp::export(mse.numeric)]]
double mse(const Rcpp::NumericVector& actual, const Rcpp::NumericVector& predicted)
{
    // 1) extract pointers to 
    // to data, and size
    const double* ptr_actual    = actual.begin();
    const double* ptr_predicted = predicted.begin();
    std::size_t n = actual.size();

    // 2) calculate and
    // return value
    return MSE::compute(ptr_actual, ptr_predicted, n);
}

//' @rdname mse
//' @method weighted.mse numeric
//' @export
// [[Rcpp::export(weighted.mse.numeric)]]
double weighted_mse(const Rcpp::NumericVector& actual, const Rcpp::NumericVector& predicted, const Rcpp::NumericVector& w)
{
    // 1) extract pointers to 
    // to data, and size
    const double* ptr_actual    = actual.begin();
    const double* ptr_predicted = predicted.begin();
    const double* ptr_w         = w.begin();
    std::size_t n = actual.size();

    // 2) calculate and
    // return value
    return MSE::compute(ptr_actual, ptr_predicted, ptr_w, n);
}
