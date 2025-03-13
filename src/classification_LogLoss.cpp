#include <Rcpp.h>
#include "classification_LogLoss.h"

//' @rdname logloss
//' @method logloss factor
//' @export
// [[Rcpp::export(logloss.factor)]]
double LogLoss(const Rcpp::IntegerVector& actual, 
               const Rcpp::NumericMatrix& response, 
               const bool normalize = true)
{
    // 1) Extract pointers
    const int*    ptr_actual   = actual.begin();
    const double* ptr_response = response.begin();
    
    // 2) Get sizes
    const std::size_t n     = actual.size();
    const std::size_t nrows = response.nrow();

    // 3) Compute
    return LogLoss::compute(ptr_actual, ptr_response, n, nrows, normalize);
}

//' @rdname logloss
//' @method weighted.logloss factor
//' @export
// [[Rcpp::export(weighted.logloss.factor)]]
double weighted_LogLoss(const Rcpp::IntegerVector& actual, 
                        const Rcpp::NumericMatrix& response, 
                        const Rcpp::NumericVector& w, 
                        const bool normalize = true)
{
    // 1) Extract pointers
    const int*    ptr_actual   = actual.begin();
    const double* ptr_response = response.begin();
    const double* ptr_w        = w.begin();

    // 2) Get sizes
    const std::size_t n     = actual.size();
    const std::size_t nrows = response.nrow();

    // 3) Compute
    return LogLoss::compute(ptr_actual, ptr_response, ptr_w, n, nrows, normalize);
}
