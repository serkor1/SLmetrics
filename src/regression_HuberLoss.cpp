#include <Rcpp.h>
#include "regression_HuberLoss.h"
using namespace Rcpp;

//' @rdname huberloss
//' @method huberloss numeric
//' @export
// [[Rcpp::export(huberloss.numeric)]]
double huberloss(const Rcpp::NumericVector& actual, const Rcpp::NumericVector& predicted, double delta = 1.0)
{
    // 1) Extract pointers and size
    const double* ptr_actual    = actual.begin();
    const double* ptr_predicted = predicted.begin();
    std::size_t n = actual.size();

    // 2) Compute unweighted Huber loss
    return HuberLoss::compute(ptr_actual, ptr_predicted, n, delta);
}

//' @rdname huberloss
//' @method weighted.huberloss numeric
//' @export
// [[Rcpp::export(weighted.huberloss.numeric)]]
double weighted_huberloss(const Rcpp::NumericVector& actual, const Rcpp::NumericVector& predicted, const Rcpp::NumericVector& w, double delta = 1.0)
{
    // 1) Extract pointers and size
    const double* ptr_actual    = actual.begin();
    const double* ptr_predicted = predicted.begin();
    const double* ptr_w         = w.begin();
    std::size_t n = actual.size();

    // 2) Compute weighted Huber loss
    return HuberLoss::compute(ptr_actual, ptr_predicted, ptr_w, n, delta);
}
