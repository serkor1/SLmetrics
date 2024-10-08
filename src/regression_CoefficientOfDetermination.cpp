#include <Rcpp.h>
using namespace Rcpp;

//' Compute the \eqn{R^2}
//'
//' @description
//' The [rsq()]-function calculates the \eqn{R^2}, the [coefficient of determination](https://en.wikipedia.org/wiki/Coefficient_of_determination), between the ovserved
//' and predicted <[numeric]> vectors. By default [rsq()] returns the unadjusted \eqn{R^2}. For adjusted \eqn{R^2} set \eqn{k = \kappa - 1}, where \eqn{\kappa} is the number of parameters.
//'
//' @usage
//' # `rsq()`-function
//' rsq(
//'   actual,
//'   predicted,
//'   k = 0
//' )
//'
//' @inherit huberloss
//' @param k A <[numeric]>-vector of [length] 1. 0 by default. If \eqn{k>0}
//' the function returns the adjusted \eqn{R^2}.
//'
//' @section Calculation:
//'
//' The metric is calculated as follows,
//'
//' \deqn{
//'   R^2 = 1 - \frac{\text{SSE}}{\text{SST}} \frac{n-1}{n - (k + 1)}
//' }
//'
//' Where \eqn{\text{SSE}} is the sum of squared errors, \eqn{\text{SST}} is total sum of squared errors, \eqn{n} is the number of observations, and \eqn{k} is the number of non-constant parameters.
//'
//' @family regression
//'
// [[Rcpp::export]]
double rsq(
    const NumericVector& actual,
    const NumericVector& predicted,
    const double k = 0) {

  // Get the size of the vectors
  const std::size_t n = actual.size();

  // Calculate the mean of actual values
  double mean_actual = std::accumulate(actual.begin(), actual.end(), 0.0) / n;

  // Calculate SSE and SSR
  double SSE = 0.0;
  double SST = 0.0;

  for (std::size_t i = 0; i < n; ++i) {
    const double actual_val = actual[i];
    const double predicted_val = predicted[i];

    SSE += (actual_val - predicted_val) * (actual_val - predicted_val);
    SST += (actual_val - mean_actual) * (actual_val - mean_actual);
  }

  // Calculate R-squared
  return 1.0 - (SSE / SST) * ((n - 1))/(n - (k + 1));
}
