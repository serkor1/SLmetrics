#ifndef REGRESSION_SYMMETRICMEANABSOLUTEPERCENTAGEERROR_H
#define REGRESSION_SYMMETRICMEANABSOLUTEPERCENTAGEERROR_H

#include <Rcpp.h>
#include <cmath>
using namespace Rcpp;

// Unweighted SMAPE Calculation
inline __attribute__((always_inline)) double _metric_(const NumericVector& actual, const NumericVector& predicted) {
  const std::size_t n = actual.size();
  double output = 0.0;

  const double* actual_ptr = actual.begin();
  const double* predicted_ptr = predicted.begin();

  int i = 0;
  int limit = n - (n % 4);

  for (; i < limit; i += 4) {
    double denominator0 = std::abs(actual_ptr[i]) + std::abs(predicted_ptr[i]);
    double denominator1 = std::abs(actual_ptr[i + 1]) + std::abs(predicted_ptr[i + 1]);
    double denominator2 = std::abs(actual_ptr[i + 2]) + std::abs(predicted_ptr[i + 2]);
    double denominator3 = std::abs(actual_ptr[i + 3]) + std::abs(predicted_ptr[i + 3]);

    if (denominator0 != 0) {
      double difference0 = std::abs(actual_ptr[i] - predicted_ptr[i]) / (denominator0 / 2);
      output += difference0;
    }

    if (denominator1 != 0) {
      double difference1 = std::abs(actual_ptr[i + 1] - predicted_ptr[i + 1]) / (denominator1 / 2);
      output += difference1;
    }

    if (denominator2 != 0) {
      double difference2 = std::abs(actual_ptr[i + 2] - predicted_ptr[i + 2]) / (denominator2 / 2);
      output += difference2;
    }

    if (denominator3 != 0) {
      double difference3 = std::abs(actual_ptr[i + 3] - predicted_ptr[i + 3]) / (denominator3 / 2);
      output += difference3;
    }
  }

  for (; i < n; ++i) {
    double denominator = std::abs(actual_ptr[i]) + std::abs(predicted_ptr[i]);
    if (denominator != 0) {
      double difference = std::abs(actual_ptr[i] - predicted_ptr[i]) / (denominator / 2);
      output += difference;
    }
  }

  return (output / n);
}

// Weighted SMAPE Calculation
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
    double total_abs0 = std::abs(actual_ptr[i]) + std::abs(predicted_ptr[i]);
    double total_abs1 = std::abs(actual_ptr[i + 1]) + std::abs(predicted_ptr[i + 1]);
    double total_abs2 = std::abs(actual_ptr[i + 2]) + std::abs(predicted_ptr[i + 2]);
    double total_abs3 = std::abs(actual_ptr[i + 3]) + std::abs(predicted_ptr[i + 3]);

    if (total_abs0 != 0) {
      numerator += std::abs(actual_ptr[i] - predicted_ptr[i]) / (total_abs0 / 2) * w_ptr[i];
      denominator += w_ptr[i];
    }

    if (total_abs1 != 0) {
      numerator += std::abs(actual_ptr[i + 1] - predicted_ptr[i + 1]) / (total_abs1 / 2) * w_ptr[i + 1];
      denominator += w_ptr[i + 1];
    }

    if (total_abs2 != 0) {
      numerator += std::abs(actual_ptr[i + 2] - predicted_ptr[i + 2]) / (total_abs2 / 2) * w_ptr[i + 2];
      denominator += w_ptr[i + 2];
    }

    if (total_abs3 != 0) {
      numerator += std::abs(actual_ptr[i + 3] - predicted_ptr[i + 3]) / (total_abs3 / 2) * w_ptr[i + 3];
      denominator += w_ptr[i + 3];
    }
  }

  for (; i < n; ++i) {
    double total_abs = std::abs(actual_ptr[i]) + std::abs(predicted_ptr[i]);
    if (total_abs != 0) {
      numerator += std::abs(actual_ptr[i] - predicted_ptr[i]) / (total_abs / 2) * w_ptr[i];
      denominator += w_ptr[i];
    }
  }

  return numerator / denominator;
}

#endif //REGRESSION_SYMMETRICMEANABSOLUTEPERCENTAGEERROR_H
