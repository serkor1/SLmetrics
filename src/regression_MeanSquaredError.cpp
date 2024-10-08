#include <Rcpp.h>

//' Compute the \eqn{\text{mean squared error}}
//'
//' The [mse()]- and [wmse()]-function computes the simple and weighted [mean squared error](https://en.wikipedia.org/wiki/Mean_squared_error) between
//' the observed and predicted <[numeric]> vectors. If `w` is not [NULL], the function returns the weighted mean squared error.
//' @usage
//' # `mse()`-function
//' mse(
//'   actual,
//'   predicted
//' )
//'
//' @inherit huberloss
//'
//' @example man/examples/scr_mse.R
//'
//' @section Calculation:
//'
//' The metric is calculated as,
//'
//' \deqn{
//'   \frac{1}{n} \sum_i^n (y_i - \upsilon_i)^2
//' }
//'
//' Where \eqn{y_i} and \eqn{\upsilon_i} are the `actual` and `predicted` values respectively. If \eqn{\text{w}} is not [NULL], the weighted version is calculated.
//'
//' @family regression
//' @export
// [[Rcpp::export]]
double mse(
    const Rcpp::NumericVector& actual,
    const Rcpp::NumericVector& predicted) {

  // This function calculates the MSE
  // between the two numeric vectors
  // NOTE: The function doesn't check
  // for equality in length before calculating
  // the final result.

  // 1) calculate the size of the vectors
  const std::size_t n = actual.size();

  // 2) point to the beginning of
  // each vector
  const double* actual_ptr = actual.begin();
  const double* predicted_ptr = predicted.begin();

  // 3) declare the placeholde
  // for the output
  double output = 0.0;

  // 4) loop through the values
  // in each vector
  for (std::size_t i = 0; i < n; ++i) {
    double difference = actual_ptr[i] - predicted_ptr[i];
    output += difference * difference;
  }

  // 5) return the mean of the value
  return output / n;
}


//' @rdname mse
//'
//' @usage
//' # `wmse()`-function
//' wmse(
//'   actual,
//'   predicted,
//'   w
//' )
//' @export
// [[Rcpp::export]]
double wmse(
   const Rcpp::NumericVector& actual,
   const Rcpp::NumericVector& predicted,
   const Rcpp::NumericVector& w) {

 // This function calculates the MSE
 // between the two numeric vectors
 // NOTE: The function doesn't check
 // for equality in length before calculating
 // the final result.

 // 1) calculate the size of the vectors
 const std::size_t n = actual.size();

 // 2) point to the beginning of
 // each vector
 const double* actual_ptr = actual.begin();
 const double* predicted_ptr = predicted.begin();
 const double* w_ptr = w.begin();

 // 3) declare the placeholde
 // for the output
 double numerator = 0.0;
 double denominator = 0.0;
 // 4) loop through the values
 // in each vector
 for (std::size_t i = 0; i < n; ++i) {
   double difference = actual_ptr[i] - predicted_ptr[i];
   numerator += difference * difference * w_ptr[i];
   denominator += w_ptr[i];
 }

 // 5) return the mean of the value
 return numerator / denominator;
}
