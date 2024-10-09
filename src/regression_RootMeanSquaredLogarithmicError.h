#ifndef REGRESSION_ROOTMEANSQUAREDLOGARITHMICERROR_H
#define REGRESSION_ROOTMEANSQUAREDLOGARITHMICERROR_H
#include <Rcpp.h>
#include <cmath>
using namespace Rcpp;

// Unweighted RMSLE Calculation
inline __attribute__((always_inline)) double _metric_(const NumericVector& actual, const NumericVector& predicted) {
  const std::size_t n = actual.size();
  double output = 0.0;

  const double* actual_ptr = actual.begin();
  const double* predicted_ptr = predicted.begin();

  int i = 0;
  int limit = n - (n % 4);

  for (; i < limit; i += 4) {
    double diff0 = std::log(actual_ptr[i] + 1) - std::log(predicted_ptr[i] + 1);
    double diff1 = std::log(actual_ptr[i + 1] + 1) - std::log(predicted_ptr[i + 1] + 1);
    double diff2 = std::log(actual_ptr[i + 2] + 1) - std::log(predicted_ptr[i + 2] + 1);
    double diff3 = std::log(actual_ptr[i + 3] + 1) - std::log(predicted_ptr[i + 3] + 1);

    output += diff0 * diff0;
    output += diff1 * diff1;
    output += diff2 * diff2;
    output += diff3 * diff3;
  }

  for (; i < n; ++i) {
    double diff = std::log(actual_ptr[i] + 1) - std::log(predicted_ptr[i] + 1);
    output += diff * diff;
  }

  return std::sqrt(output / n);
}

// Weighted RMSLE Calculation
inline __attribute__((always_inline)) double _metric_(const NumericVector& actual, const NumericVector& predicted, const NumericVector& w) {
  const std::size_t n = actual.size();
  double numerator = 0.0;
  double denominator = 0.0;

  const double* actual_ptr = actual.begin();
  const double* predicted_ptr = predicted.begin();
  const double* w_ptr = w.begin();

  int i = 0;
  int limit = n - (n % 4);

  for (; i < limit; i += 4) {
    double diff0 = std::log(actual_ptr[i] + 1) - std::log(predicted_ptr[i] + 1);
    double weight0 = w_ptr[i];

    double diff1 = std::log(actual_ptr[i + 1] + 1) - std::log(predicted_ptr[i + 1] + 1);
    double weight1 = w_ptr[i + 1];

    double diff2 = std::log(actual_ptr[i + 2] + 1) - std::log(predicted_ptr[i + 2] + 1);
    double weight2 = w_ptr[i + 2];

    double diff3 = std::log(actual_ptr[i + 3] + 1) - std::log(predicted_ptr[i + 3] + 1);
    double weight3 = w_ptr[i + 3];

    numerator += (diff0 * diff0 * weight0);
    numerator += (diff1 * diff1 * weight1);
    numerator += (diff2 * diff2 * weight2);
    numerator += (diff3 * diff3 * weight3);

    denominator += weight0 + weight1 + weight2 + weight3;
  }

  for (; i < n; ++i) {
    double diff = std::log(actual_ptr[i] + 1) - std::log(predicted_ptr[i] + 1);
    double weight = w_ptr[i];
    numerator += (diff * diff * weight);
    denominator += weight;
  }

  return std::sqrt(numerator / denominator);
}

#endif //REGRESSION_ROOTMEANSQUAREDLOGARITHMICERROR_H
