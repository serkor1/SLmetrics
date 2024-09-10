#include <Rcpp.h>
using namespace Rcpp;
//' Weighted Huber Loss
//'
//' @description
//' Calculate the Weighted Huber Loss of two <[numeric]> vectors.
//'
//' @usage
//' whuberloss(
//'   actual,
//'   predicted,
//'   delta = 1,
//'   w
//' )
//'
//' @param actual A <[numeric]>-vector of length N.
//' @param predicted A <[numeric]>-vector of length N.
//' @param delta A <[numeric]>-vector of length 1. 1 by default.
//' @param w An optional  <[numeric]>-vector of [length] n. [NULL] by default.
//'
//' @details
//'
//' The Huber Loss is calculated as,
//'
//' \deqn{
//'  \frac{1}{2} (y_i - \hat{y}_i)^2 ~for~ |y_i - \hat{y}_i| \leq \delta
//' }
//'
//' \deqn{
//'   \delta |y_i-\hat{y}_i|-\frac{1}{2} \delta^2 ~for~ |y_i - \hat{y}_i| > \delta
//' }
//'
//' for each \eqn{i},
//'
//'
//' @example man/examples/scr_huberloss.R
//'
//'
//' @family regression
//' @returns A <[numeric]>-value of length 1.
//' @export
// [[Rcpp::export]]
double whuberloss(
    const NumericVector& actual,
    const NumericVector& predicted,
    const NumericVector& w,
    const double& delta = 1) {

  /*
   * This function returns the Huber Loss
   * using weighted or unweighted means.
   *
   * NOTE: It needs to be optimized further
   *
   */

  // Get the size of the vectors
  const std::size_t n = actual.size();

  // Initialize the output variable
  double numerator = 0.0;
  double denominator = 0.0;

  const double* actual_ptr = actual.begin();
  const double* predicted_ptr = predicted.begin();
  const double* w_ptr = w.begin();

  for (std::size_t i = 0; i < n; ++i) {

    double diff = actual_ptr[i] - predicted_ptr[i];
    double abs_diff = std::abs(diff);
    denominator += w_ptr[i];

    if (abs_diff <= delta) {
      numerator += 0.5 * diff * diff * w_ptr[i];
    } else {
      numerator += delta * (abs_diff - 0.5 * delta) * w_ptr[i];
    }

  }

  return numerator / denominator;

}
