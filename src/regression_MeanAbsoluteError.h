#ifndef REGRESSION_MEANABSOLUTEERROR_H
#define REGRESSION_MEANABSOLUTEERROR_H

#include <Rcpp.h>
#include <cmath>
using namespace Rcpp;

// Unweighted Mean Absolute Error Calculation
inline __attribute__((always_inline)) double _metric_(const NumericVector& actual, const NumericVector& predicted) {
  const std::size_t n = actual.size();
  const double* actual_ptr = actual.begin();
  const double* predicted_ptr = predicted.begin();

  double output = 0.0;
  int i = 0;
  int limit = n - (n % 4);

  for (; i < limit; i += 4) {
    output += std::abs(actual_ptr[i] - predicted_ptr[i]);
    output += std::abs(actual_ptr[i + 1] - predicted_ptr[i + 1]);
    output += std::abs(actual_ptr[i + 2] - predicted_ptr[i + 2]);
    output += std::abs(actual_ptr[i + 3] - predicted_ptr[i + 3]);
  }

  for (; i < n; ++i) {
    output += std::abs(actual_ptr[i] - predicted_ptr[i]);
  }

  return output / n;
}

// Weighted Mean Absolute Error Calculation
inline __attribute__((always_inline)) double _metric_(const NumericVector& actual, const NumericVector& predicted, const NumericVector& w) {
  const std::size_t n = actual.size();
  const double* actual_ptr = actual.begin();
  const double* predicted_ptr = predicted.begin();
  const double* w_ptr = w.begin();

  double numerator = 0.0;
  double denominator = 0.0;

  int i = 0;
  int limit = n - (n % 4);

  for (; i < limit; i += 4) {
    double diff0 = std::abs(actual_ptr[i] - predicted_ptr[i]);
    double diff1 = std::abs(actual_ptr[i + 1] - predicted_ptr[i + 1]);
    double diff2 = std::abs(actual_ptr[i + 2] - predicted_ptr[i + 2]);
    double diff3 = std::abs(actual_ptr[i + 3] - predicted_ptr[i + 3]);

    numerator += diff0 * w_ptr[i];
    numerator += diff1 * w_ptr[i + 1];
    numerator += diff2 * w_ptr[i + 2];
    numerator += diff3 * w_ptr[i + 3];

    denominator += w_ptr[i] + w_ptr[i + 1] + w_ptr[i + 2] + w_ptr[i + 3];
  }

  for (; i < n; ++i) {
    double difference = std::abs(actual_ptr[i] - predicted_ptr[i]);
    numerator += difference * w_ptr[i];
    denominator += w_ptr[i];
  }

  return numerator / denominator;
}

#endif
