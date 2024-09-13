#include <Rcpp.h>

//' Mean Squared Error (MSE)
//'
//' Calculate the MSE using the [mse()]-function for the (arithmetic) simple mean, or [wmse()]-function for the (arithmetic) weighted mean.
//'
//' @usage
//' # simple mean
//' mse(
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
//' # weighted mean
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
