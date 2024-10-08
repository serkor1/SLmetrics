#include <Rcpp.h>
using namespace Rcpp;

//' Compute the \eqn{\text{huber loss}}
//'
//' @description
//' The [huberloss()]- and [whuberloss()]-function computes the simple and weighted [huber loss](https://en.wikipedia.org/wiki/Huber_loss) between
//' the predicted and observed <[numeric]> vectors.
//'
//' @usage
//' # `huberloss()`-function
//' huberloss(
//'   actual,
//'   predicted,
//'   delta = 1
//' )
//'
//' @param actual A <[numeric]>-vector of [length] \eqn{n}. The observed (continuous) response variable.
//' @param predicted A <[numeric]>-vector of [length] \eqn{n}. The estimated (continuous) response variable.
//' @param delta A <[numeric]>-vector of [length] 1. 1 by default. The threshold value for switch between functions (see calculation).
//'
//' @section Calculation:
//'
//' The metric is calculated as follows,
//'
//' \deqn{
//'  \frac{1}{2} (y - \upsilon)^2 ~for~ |y - \upsilon| \leq \delta
//' }
//'
//' and
//'
//' \deqn{
//'   \delta |y-\upsilon|-\frac{1}{2} \delta^2 ~for~ \text{otherwise}
//' }
//'
//' where \eqn{y} and \eqn{\upsilon} are the `actual` and `predicted` values respectively. If `w` is not [NULL], then all values
//' are aggregated using the weights.
//'
//'
//' @example man/examples/scr_huberloss.R
//'
//'
//' @family regression
//'
//' @returns A <[numeric]> vector of [length] 1.
//'
//' @export
// [[Rcpp::export]]
double huberloss(
    const NumericVector& actual,
    const NumericVector& predicted,
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
  double output = 0.0;

  const double* actual_ptr = actual.begin();
  const double* predicted_ptr = predicted.begin();

  for (std::size_t i = 0; i < n; ++i) {

    double diff = actual_ptr[i] - predicted_ptr[i];
    double abs_diff = std::abs(diff);

    if (abs_diff <= delta) {

      output += 0.5 * diff * diff;

    } else {

      output += delta * (abs_diff - 0.5 * delta);

    }
  }

  // Return the mean Huber loss
  return output / n;

}

//' @rdname huberloss
//' @usage
//' # `whuberloss()`-function
//' whuberloss(
//'   actual,
//'   predicted,
//'   w,
//'   delta = 1
//' )
//'
//' @param w A <[numeric]>-vector of [length] \eqn{n}. The weight assigned to each observation in the data. See [stats::weighted.mean()] for more details.
//'
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
