#include <Rcpp.h>
#include <algorithm>
using namespace Rcpp;

//' Binary Cross Entropy
//'
//' @param actual placeholder
//' @param response placeholder
//'
//' @family classification
double entropy(
  const NumericVector& actual,
  const NumericVector& response) {

  const size_t n = actual.size();
  double loss = 0.0;

  for (size_t i = 0; i < n; ++i) {
    // Ensure that the predicted values are within the valid range
    const double pred = std::max(std::min(response[i], 1.0 - 1e-15), 1e-15);
    loss += actual[i] * std::log(pred) + (1 - actual[i]) * std::log(1 - pred);
  }

  // Return the average binary cross-entropy loss
  return -loss / n;

}

