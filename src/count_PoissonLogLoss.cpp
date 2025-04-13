#include <Rcpp.h>
#include "count_PoissonLogLoss.h"

//' @templateVar .FUN logloss
//' @templateVar .METHOD integer
//' @template classification_entropy_inherit
//' @export
// [[Rcpp::export(logloss.integer)]]
double PoissonLogLoss(const Rcpp::IntegerVector& actual, 
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
    return PoissonLogLoss::compute(ptr_actual, ptr_response, n, normalize);
}

//' @templateVar .FUN weighted.logloss
//' @templateVar .METHOD integer
//' @template classification_entropy_inherit
//' @export
// [[Rcpp::export(weighted.logloss.integer)]]
double weighted_PoissonLogLoss(const Rcpp::IntegerVector& actual, 
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
    return PoissonLogLoss::compute(ptr_actual, ptr_response, ptr_w, n, normalize);
}
