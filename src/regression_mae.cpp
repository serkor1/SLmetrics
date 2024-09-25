#include <Rcpp.h>

//' Compute the \eqn{\text{mean absolute error}}
//'
//' The [mae()]- and [wmae()]-function computes the simple and weighted [mean absolute error](https://en.wikipedia.org/wiki/Mean_absolute_error) between
//' the observed and predicted <[numeric]> vectors. If `w` is not [NULL] the function returns the weighted mean absolute error.
//'
//' @usage
//' # `mae()`-function
//' mae(
//'   actual,
//'   predicted
//' )
//'
//' @inherit huberloss
//'
//' @example man/examples/scr_mae.R
//'
//' @section Calculation:
//'
//' The metric is calulated as follows,
//'
//' \deqn{
//'   \frac{\sum_i^n |y_i - \upsilon_i|}{n}
//' }
//'
//' If \eqn{w} is not [NULL] the function returns the weigthed version.
//'
//' @family regression
//'
//' @export
// [[Rcpp::export]]
double mae(
    const Rcpp::NumericVector& actual,
    const Rcpp::NumericVector& predicted) {

  // This function calculates the MAE
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

    double difference = std::abs(actual_ptr[i] - predicted_ptr[i]);
    output += difference;

  }

  // 5) return the mean of the value
  return output / n;
}

//' @rdname mae
//'
//' @usage
//' # `wmae()`-function
//' wmae(
//'   actual,
//'   predicted,
//'   w
//' )
//' @export
// [[Rcpp::export]]
double wmae(
    const Rcpp::NumericVector& actual,
    const Rcpp::NumericVector& predicted,
    const Rcpp::NumericVector& w) {

  // This function calculates the MAE
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

    double difference = std::abs(actual_ptr[i] - predicted_ptr[i]);
    numerator   += difference * w_ptr[i];
    denominator +=  w_ptr[i];

  }

  // 5) return the mean of the value
  return numerator / denominator;
}

