#include <Rcpp.h>
#include "regression_SymmetricMeanAbsolutePercentageError.h"
using namespace Rcpp;

//' @rdname smape
//' @method smape numeric
//' @export
// [[Rcpp::export(smape.numeric)]]
double smape(const Rcpp::NumericVector& actual, const Rcpp::NumericVector& predicted)
{
    // 1) extract pointers to 
    // to data, and size
    const double* ptr_actual    = actual.begin();
    const double* ptr_predicted = predicted.begin();
    std::size_t n = actual.size();

    // 2) calculate and
    // return value
    return SMAPE::compute(ptr_actual, ptr_predicted, n);
}

//' @rdname smape
//' @method weighted.smape numeric
//' @export
// [[Rcpp::export(weighted.smape.numeric)]]
double weighted_smape(const Rcpp::NumericVector& actual, const Rcpp::NumericVector& predicted, const Rcpp::NumericVector& w)
{
    // 1) extract pointers to 
    // to data, and size    
    const double* ptr_actual    = actual.begin();
    const double* ptr_predicted = predicted.begin();
    const double* ptr_w         = w.begin();
    std::size_t n = actual.size();

    // 2) calculate and
    // return value
    return SMAPE::compute(ptr_actual, ptr_predicted, ptr_w, n);
}
