#ifndef REGRESSION_HUBERLOSS_H
#define REGRESSION_HUBERLOSS_H
#include <Rcpp.h>
#include <cmath>
using namespace Rcpp;

// Unweighted Huber Loss Calculation
inline __attribute__((always_inline)) double _metric_(const NumericVector& actual, const NumericVector& predicted, const double& delta) {
  const std::size_t n = actual.size();
  double output = 0.0;

  const double* actual_ptr = actual.begin();
  const double* predicted_ptr = predicted.begin();

  int i = 0;
  int limit = n - (n % 4);

  for (; i < limit; i += 4) {
    double diff0 = actual_ptr[i] - predicted_ptr[i];
    double abs_diff0 = std::abs(diff0);

    double diff1 = actual_ptr[i + 1] - predicted_ptr[i + 1];
    double abs_diff1 = std::abs(diff1);

    double diff2 = actual_ptr[i + 2] - predicted_ptr[i + 2];
    double abs_diff2 = std::abs(diff2);

    double diff3 = actual_ptr[i + 3] - predicted_ptr[i + 3];
    double abs_diff3 = std::abs(diff3);

    output += (abs_diff0 <= delta) ? 0.5 * diff0 * diff0 : delta * (abs_diff0 - 0.5 * delta);
    output += (abs_diff1 <= delta) ? 0.5 * diff1 * diff1 : delta * (abs_diff1 - 0.5 * delta);
    output += (abs_diff2 <= delta) ? 0.5 * diff2 * diff2 : delta * (abs_diff2 - 0.5 * delta);
    output += (abs_diff3 <= delta) ? 0.5 * diff3 * diff3 : delta * (abs_diff3 - 0.5 * delta);
  }

  for (; i < n; ++i) {
    double diff = actual_ptr[i] - predicted_ptr[i];
    double abs_diff = std::abs(diff);

    output += (abs_diff <= delta) ? 0.5 * diff * diff : delta * (abs_diff - 0.5 * delta);
  }

  return output / n;
}

// Weighted Huber Loss Calculation
inline __attribute__((always_inline)) double _metric_(const NumericVector& actual, const NumericVector& predicted, const double& delta, const NumericVector& w) {
  const std::size_t n = actual.size();
  double numerator = 0.0;
  double denominator = 0.0;

  const double* actual_ptr = actual.begin();
  const double* predicted_ptr = predicted.begin();
  const double* w_ptr = w.begin();

  int i = 0;
  int limit = n - (n % 4);

  for (; i < limit; i += 4) {
    double diff0 = actual_ptr[i] - predicted_ptr[i];
    double abs_diff0 = std::abs(diff0);
    double weight0 = w_ptr[i];

    double diff1 = actual_ptr[i + 1] - predicted_ptr[i + 1];
    double abs_diff1 = std::abs(diff1);
    double weight1 = w_ptr[i + 1];

    double diff2 = actual_ptr[i + 2] - predicted_ptr[i + 2];
    double abs_diff2 = std::abs(diff2);
    double weight2 = w_ptr[i + 2];

    double diff3 = actual_ptr[i + 3] - predicted_ptr[i + 3];
    double abs_diff3 = std::abs(diff3);
    double weight3 = w_ptr[i + 3];

    denominator += weight0 + weight1 + weight2 + weight3;

    numerator += (abs_diff0 <= delta) ? 0.5 * diff0 * diff0 * weight0 : delta * (abs_diff0 - 0.5 * delta) * weight0;
    numerator += (abs_diff1 <= delta) ? 0.5 * diff1 * diff1 * weight1 : delta * (abs_diff1 - 0.5 * delta) * weight1;
    numerator += (abs_diff2 <= delta) ? 0.5 * diff2 * diff2 * weight2 : delta * (abs_diff2 - 0.5 * delta) * weight2;
    numerator += (abs_diff3 <= delta) ? 0.5 * diff3 * diff3 * weight3 : delta * (abs_diff3 - 0.5 * delta) * weight3;
  }

  for (; i < n; ++i) {
    double diff = actual_ptr[i] - predicted_ptr[i];
    double abs_diff = std::abs(diff);
    double weight = w_ptr[i];

    denominator += weight;
    numerator += (abs_diff <= delta) ? 0.5 * diff * diff * weight : delta * (abs_diff - 0.5 * delta) * weight;
  }

  return numerator / denominator;
}

#endif //REGRESSION_HUBERLOSS_H
