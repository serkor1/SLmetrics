#ifndef REGRESSION_CONCORDANCECORRELATIONCOEFFICIENT_H
#define REGRESSION_CONCORDANCECORRELATIONCOEFFICIENT_H

#include <Rcpp.h>
#include <cmath>
#include <numeric>
using namespace Rcpp;

// Unweighted Concordance Correlation Coefficient Calculation
inline __attribute__((always_inline)) double _metric_(const NumericVector& actual, const NumericVector& predicted, bool correction) {
  const std::size_t n = actual.size();
  const double* actual_ptr = actual.begin();
  const double* predicted_ptr = predicted.begin();

  // Calculate means
  double mean_actual = 0.0;
  double mean_predicted = 0.0;

  int i = 0;
  int limit = n - (n % 4);

  for (; i < limit; i += 4) {
    mean_actual += actual_ptr[i];
    mean_actual += actual_ptr[i + 1];
    mean_actual += actual_ptr[i + 2];
    mean_actual += actual_ptr[i + 3];

    mean_predicted += predicted_ptr[i];
    mean_predicted += predicted_ptr[i + 1];
    mean_predicted += predicted_ptr[i + 2];
    mean_predicted += predicted_ptr[i + 3];
  }

  for (; i < n; ++i) {
    mean_actual += actual_ptr[i];
    mean_predicted += predicted_ptr[i];
  }

  mean_actual /= n;
  mean_predicted /= n;

  // Calculate variances and covariance
  double var_actual = 0.0;
  double var_predicted = 0.0;
  double covariance = 0.0;

  i = 0;
  for (; i < limit; i += 4) {
    var_actual += (actual_ptr[i] - mean_actual) * (actual_ptr[i] - mean_actual);
    var_actual += (actual_ptr[i + 1] - mean_actual) * (actual_ptr[i + 1] - mean_actual);
    var_actual += (actual_ptr[i + 2] - mean_actual) * (actual_ptr[i + 2] - mean_actual);
    var_actual += (actual_ptr[i + 3] - mean_actual) * (actual_ptr[i + 3] - mean_actual);

    var_predicted += (predicted_ptr[i] - mean_predicted) * (predicted_ptr[i] - mean_predicted);
    var_predicted += (predicted_ptr[i + 1] - mean_predicted) * (predicted_ptr[i + 1] - mean_predicted);
    var_predicted += (predicted_ptr[i + 2] - mean_predicted) * (predicted_ptr[i + 2] - mean_predicted);
    var_predicted += (predicted_ptr[i + 3] - mean_predicted) * (predicted_ptr[i + 3] - mean_predicted);

    covariance += (actual_ptr[i] - mean_actual) * (predicted_ptr[i] - mean_predicted);
    covariance += (actual_ptr[i + 1] - mean_actual) * (predicted_ptr[i + 1] - mean_predicted);
    covariance += (actual_ptr[i + 2] - mean_actual) * (predicted_ptr[i + 2] - mean_predicted);
    covariance += (actual_ptr[i + 3] - mean_actual) * (predicted_ptr[i + 3] - mean_predicted);
  }

  for (; i < n; ++i) {
    var_actual += (actual_ptr[i] - mean_actual) * (actual_ptr[i] - mean_actual);
    var_predicted += (predicted_ptr[i] - mean_predicted) * (predicted_ptr[i] - mean_predicted);
    covariance += (actual_ptr[i] - mean_actual) * (predicted_ptr[i] - mean_predicted);
  }

  var_actual /= n;
  var_predicted /= n;
  covariance /= n;

  // Apply bias correction if requested
  if (correction) {
    var_actual *= (n - 1.0) / n;
    var_predicted *= (n - 1.0) / n;
    covariance *= (n - 1.0) / n;
  }

  // Calculate the Concordance Correlation Coefficient
  return (2.0 * covariance) / (var_actual + var_predicted + std::pow(mean_actual - mean_predicted, 2));
}

// Weighted Concordance Correlation Coefficient Calculation
inline __attribute__((always_inline)) double _metric_(const NumericVector& actual, const NumericVector& predicted, const NumericVector& w, bool correction) {
  const std::size_t n = actual.size();
  const double* actual_ptr = actual.begin();
  const double* predicted_ptr = predicted.begin();
  const double* w_ptr = w.begin();

  double weighted_mean_actual = 0.0;
  double weighted_mean_predicted = 0.0;
  double sum_weights = 0.0;

  for (std::size_t i = 0; i < n; ++i) {
    weighted_mean_actual += actual_ptr[i] * w_ptr[i];
    weighted_mean_predicted += predicted_ptr[i] * w_ptr[i];
    sum_weights += w_ptr[i];
  }

  weighted_mean_actual /= sum_weights;
  weighted_mean_predicted /= sum_weights;

  double weighted_var_actual = 0.0;
  double weighted_var_predicted = 0.0;
  double weighted_covariance = 0.0;

  for (std::size_t i = 0; i < n; ++i) {
    double diff_actual = actual_ptr[i] - weighted_mean_actual;
    double diff_predicted = predicted_ptr[i] - weighted_mean_predicted;

    weighted_var_actual += w_ptr[i] * diff_actual * diff_actual;
    weighted_var_predicted += w_ptr[i] * diff_predicted * diff_predicted;
    weighted_covariance += w_ptr[i] * diff_actual * diff_predicted;
  }

  weighted_var_actual /= sum_weights;
  weighted_var_predicted /= sum_weights;
  weighted_covariance /= sum_weights;

  if (correction) {
    weighted_var_actual *= (sum_weights - 1.0) / sum_weights;
    weighted_var_predicted *= (sum_weights - 1.0) / sum_weights;
    weighted_covariance *= (sum_weights - 1.0) / sum_weights;
  }

  // Calculate the Weighted Concordance Correlation Coefficient
  return (2.0 * weighted_covariance) /
    (weighted_var_actual + weighted_var_predicted + std::pow(weighted_mean_actual - weighted_mean_predicted, 2));
}

#endif //REGRESSION_CONCORDANCECORRELATIONCOEFFICIENT_H
