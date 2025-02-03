#include <Rcpp.h>
#include "regression_RootMeanSquaredError.h"
using namespace Rcpp;

//' @rdname rmse
//' @method rmse numeric
//' @export
// [[Rcpp::export(rmse.numeric)]]
double rmse(const Rcpp::NumericVector& actual, const Rcpp::NumericVector& predicted) 
{
    // 1) Extract pointers
    // to the data
    const double* ptr_actual    = actual.begin();
    const double* ptr_predicted = predicted.begin();

    // 2) Extract the size
    // of the actual vector
    std::size_t n = actual.size();

    // 3) Calculate RMSE
    return RMSE::compute(ptr_actual, ptr_predicted, n);
    

}

//' @rdname rmse
//' @method weighted.rmse numeric
//' @export
// [[Rcpp::export(weighted.rmse.numeric)]]
double weighted_rmse(const Rcpp::NumericVector& actual, const Rcpp::NumericVector& predicted, const Rcpp::NumericVector& w)
{
    // 1) Extract pointers
    // to the data
    const double* ptr_actual    = actual.begin();
    const double* ptr_predicted = predicted.begin();
    const double* ptr_w         = w.begin();

    // 2) Extract the size
    // of the actual vector
    std::size_t n = actual.size();

    // 3) Calculate RMSE
    return RMSE::compute(ptr_actual, ptr_predicted, ptr_w, n);
   
}