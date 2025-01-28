#include <Rcpp.h>
#include "regression_MeanAbsolutePercentageError.h"
using namespace Rcpp;

//' @rdname mape
//' @method mape numeric
//' @export
// [[Rcpp::export(mape.numeric)]]
double mape(const Rcpp::NumericVector& actual, const Rcpp::NumericVector& predicted)
{
    const double* ptr_actual    = actual.begin();
    const double* ptr_predicted = predicted.begin();
    std::size_t n               = actual.size();

    return MAPE::compute(ptr_actual, ptr_predicted, n);
}

//' @rdname mape
//' @method weighted.mape numeric
//' @export
// [[Rcpp::export(weighted.mape.numeric)]]
double weighted_mape(const Rcpp::NumericVector& actual, 
                     const Rcpp::NumericVector& predicted, 
                     const Rcpp::NumericVector& w)
{
    const double* ptr_actual    = actual.begin();
    const double* ptr_predicted = predicted.begin();
    const double* ptr_w         = w.begin();
    std::size_t n               = actual.size();

    return MAPE::compute(ptr_actual, ptr_predicted, ptr_w, n);
}
