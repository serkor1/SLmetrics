#include <Rcpp.h>
#include <cmath>

//' Root Mean Squared Logarithmic Error (RMSLE)
//'
//' Calculate the RMSLE using the [rmsle()]-function for the (arithmetic) simple mean, or [wrmsle()]-function for the (arithmetic) weighted mean.
//'
//' @usage
//' # simple RMSLE
//' rmsle(
//'   actual,
//'   predicted
//' )
//'
//' @inherit huberloss
//'
//' @family regression
//'
//' @export
// [[Rcpp::export]]
double rmsle(
    const Rcpp::NumericVector& actual,
    const Rcpp::NumericVector& predicted) {

  // This function calculates the RMSLE
  // between the two numeric vectors
  // NOTE: The function doesn't check
  // for equalit//' @exporty in length before calculating
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
    double difference = std::log(actual_ptr[i] + 1) - std::log(predicted_ptr[i] + 1);
    output += difference * difference;
  }

  // 5) return the squared
  // mean of the value
  return std::sqrt(output / n);
}


//' @rdname rmsle
//'
//' @usage
//' # weighted RMSLE
//' wrmsle(
//'   actual,
//'   predicted,
//'   w
//' )
//'
//' @export
 // [[Rcpp::export]]
double wrmsle(
    const Rcpp::NumericVector& actual,
    const Rcpp::NumericVector& predicted,
    const Rcpp::NumericVector& w) {

  // This function calculates the RMSLE
  // between the two numeric vectors
  // NOTE: The function doesn't check
  // for equalit//' @exporty in length before calculating
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
    double difference = std::log(actual_ptr[i] + 1) - std::log(predicted_ptr[i] + 1);
    numerator += difference * difference * w_ptr[i];
    denominator += w_ptr[i];
  }

  // 5) return the squared
  // mean of the value
  return std::sqrt(numerator / denominator);
}
