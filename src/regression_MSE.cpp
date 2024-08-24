#include <Rcpp.h>

//' Mean Square Error (MSE)
//'
//' Calculate the MSE of two <[numeric]>-vectors
//'
//' @param actual A <[numeric]>-vector of length N.
//' @param predicted A <[numeric]>-vector of length N.
//'
//' @returns A <[numeric]>-value of length 1.
//'
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
