#include <Rcpp.h>
using namespace Rcpp;

//' Huber Loss
//'
//' Calculate the huber loss of two <[numeric]> vectors.
//'
//' @param actual A <[numeric]>-vector of length N.
//' @param predicted A <[numeric]>-vector of length N.
//' @param delta A <[numeric]>-vector of length 1. 1 by default.
//'
//' @returns A <[numeric]>-value of length 1.
// [[Rcpp::export]]
double huberloss(
    const NumericVector& actual,
    const NumericVector& predicted,
    const double delta = 1) {

  // Get the size of the vectors
  const std::size_t n = actual.size();

  // Initialize the output variable
  double output = 0.0;

  // Iterate over the vectors and compute the Huber loss
  for (std::size_t i = 0; i < n; ++i) {
    double diff = actual[i] - predicted[i];
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
