#include <Rcpp.h>
#include "regression_MeanAbsoluteError.h"
using namespace Rcpp;

//' @rdname mae
//' @method mae numeric
//' @export
// [[Rcpp::export(mae.numeric)]]
double mae(const Rcpp::NumericVector& actual, const Rcpp::NumericVector& predicted)
{
    const double* ptr_actual    = actual.begin();
    const double* ptr_predicted = predicted.begin();
    std::size_t n = actual.size();

    return MAE::compute(ptr_actual, ptr_predicted, n);
}

//' @rdname mae
//' @method weighted.mae numeric
//' @export
// [[Rcpp::export(weighted.mae.numeric)]]
double weighted_mae(const Rcpp::NumericVector& actual, 
                    const Rcpp::NumericVector& predicted, 
                    const Rcpp::NumericVector& w)
{
    const double* ptr_actual    = actual.begin();
    const double* ptr_predicted = predicted.begin();
    const double* ptr_w         = w.begin();
    std::size_t n = actual.size();

    return MAE::compute(ptr_actual, ptr_predicted, ptr_w, n);
}
