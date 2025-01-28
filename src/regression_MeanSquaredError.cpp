#include <Rcpp.h>
#include "regression_MeanSquaredError.h"
using namespace Rcpp;

//' @rdname mse
//' @method mse numeric
//' @export
// [[Rcpp::export(mse.numeric)]]
double mse(const NumericVector& actual, const NumericVector& predicted)
{
    const double* ptr_actual    = actual.begin();
    const double* ptr_predicted = predicted.begin();
    std::size_t n = actual.size();

    return MSE::compute(ptr_actual, ptr_predicted, n);
}

//' @rdname mse
//' @method weighted.mse numeric
//' @export
// [[Rcpp::export(weighted.mse.numeric)]]
double weighted_mse(const NumericVector& actual, 
                    const NumericVector& predicted, 
                    const NumericVector& w)
{
    const double* ptr_actual    = actual.begin();
    const double* ptr_predicted = predicted.begin();
    const double* ptr_w         = w.begin();
    std::size_t n = actual.size();

    return MSE::compute(ptr_actual, ptr_predicted, ptr_w, n);
}
