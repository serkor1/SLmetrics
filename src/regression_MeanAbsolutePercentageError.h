//
// Created by serko on 10/10/2024.
//

#ifndef MEANABSOLUTEPERCENTAGEERROR_H
#define MEANABSOLUTEPERCENTAGEERROR_H


#include <Rcpp.h>
#include <cmath>
using namespace Rcpp;

// Unweighted MAPE Calculation
inline __attribute__((always_inline)) double _metric_(const NumericVector& actual, const NumericVector& predicted) {
  const std::size_t n = actual.size();
  double output = 0.0;

  const double* actual_ptr = actual.begin();
  const double* predicted_ptr = predicted.begin();

  int i = 0;
  int limit = n - (n % 4);

  for (; i < limit; i += 4) {
    double difference0 = std::abs((actual_ptr[i] - predicted_ptr[i]) / actual_ptr[i]);
    double difference1 = std::abs((actual_ptr[i + 1] - predicted_ptr[i + 1]) / actual_ptr[i + 1]);
    double difference2 = std::abs((actual_ptr[i + 2] - predicted_ptr[i + 2]) / actual_ptr[i + 2]);
    double difference3 = std::abs((actual_ptr[i + 3] - predicted_ptr[i + 3]) / actual_ptr[i + 3]);

    output += difference0 + difference1 + difference2 + difference3;
  }

  for (; i < n; ++i) {
    double difference = std::abs((actual_ptr[i] - predicted_ptr[i]) / actual_ptr[i]);
    output += difference;
  }

  return output / n;
}

// Weighted MAPE Calculation
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
    double difference0 = std::abs((actual_ptr[i] - predicted_ptr[i]) / actual_ptr[i]);
    double weight0 = w_ptr[i];

    double difference1 = std::abs((actual_ptr[i + 1] - predicted_ptr[i + 1]) / actual_ptr[i + 1]);
    double weight1 = w_ptr[i + 1];

    double difference2 = std::abs((actual_ptr[i + 2] - predicted_ptr[i + 2]) / actual_ptr[i + 2]);
    double weight2 = w_ptr[i + 2];

    double difference3 = std::abs((actual_ptr[i + 3] - predicted_ptr[i + 3]) / actual_ptr[i + 3]);
    double weight3 = w_ptr[i + 3];

    numerator += (difference0 * weight0);
    numerator += (difference1 * weight1);
    numerator += (difference2 * weight2);
    numerator += (difference3 * weight3);

    denominator += weight0 + weight1 + weight2 + weight3;
  }

  for (; i < n; ++i) {
    double difference = std::abs((actual_ptr[i] - predicted_ptr[i]) / actual_ptr[i]);
    double weight = w_ptr[i];
    numerator += (difference * weight);
    denominator += weight;
  }

  return numerator / denominator;
}

#endif //MEANABSOLUTEPERCENTAGEERROR_H
