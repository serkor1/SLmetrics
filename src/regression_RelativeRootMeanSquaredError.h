#ifndef REGRESSION_RelativeRootMeanSquaredError_H
#define REGRESSION_RelativeRootMeanSquaredError_H
#include <Rcpp.h>
#include <cmath>
#include <numeric> // for std::accumulate
using namespace Rcpp;


inline __attribute__((always_inline)) double _metric_(const NumericVector& actual, const NumericVector& predicted)
{
  const std::size_t n = actual.size();
  const double mean_actual = std::accumulate(actual.begin(), actual.end(), 0.0) / n;

  const double* actual_ptr = actual.begin();
  const double* predicted_ptr = predicted.begin();

  double numerator = 0.0;
  double denominator = 0.0;
  int i = 0;
  int limit = n - (n % 4);

  for (; i < limit; i += 4) {
    double diff0 = *(actual_ptr++) - *(predicted_ptr++);
    double diff1 = *(actual_ptr++) - *(predicted_ptr++);
    double diff2 = *(actual_ptr++) - *(predicted_ptr++);
    double diff3 = *(actual_ptr++) - *(predicted_ptr++);

    numerator += diff0 * diff0 + diff1 * diff1 + diff2 * diff2 + diff3 * diff3;

    double diff_mean0 = *(actual_ptr - 4) - mean_actual;
    double diff_mean1 = *(actual_ptr - 3) - mean_actual;
    double diff_mean2 = *(actual_ptr - 2) - mean_actual;
    double diff_mean3 = *(actual_ptr - 1) - mean_actual;

    denominator += diff_mean0 * diff_mean0 + diff_mean1 * diff_mean1 + diff_mean2 * diff_mean2 + diff_mean3 * diff_mean3;
  }

  for (; i < n; ++i) {
    double diff = *(actual_ptr++) - *(predicted_ptr++);
    numerator += diff * diff;

    double diff_mean = *(actual_ptr - 1) - mean_actual;
    denominator += diff_mean * diff_mean;
  }

  return std::sqrt(numerator / denominator);
}


inline __attribute__((always_inline)) double _metric_(const NumericVector& actual, const NumericVector& predicted, const NumericVector& w)
{
  const std::size_t n = actual.size();
  const double mean_actual = std::inner_product(actual.begin(), actual.end(), w.begin(), 0.0) / std::accumulate(w.begin(), w.end(), 0.0);

  const double* actual_ptr = actual.begin();
  const double* predicted_ptr = predicted.begin();
  const double* w_ptr = w.begin();

  double numerator = 0.0;
  double denominator = 0.0;
  int i = 0;
  int limit = n - (n % 4);

  for (; i < limit; i += 4) {
    double w0 = *(w_ptr++);
    double w1 = *(w_ptr++);
    double w2 = *(w_ptr++);
    double w3 = *(w_ptr++);

    double diff0 = *(actual_ptr++) - *(predicted_ptr++);
    double diff1 = *(actual_ptr++) - *(predicted_ptr++);
    double diff2 = *(actual_ptr++) - *(predicted_ptr++);
    double diff3 = *(actual_ptr++) - *(predicted_ptr++);

    numerator += w0 * diff0 * diff0 + w1 * diff1 * diff1 + w2 * diff2 * diff2 + w3 * diff3 * diff3;

    double diff_mean0 = *(actual_ptr - 4) - mean_actual;
    double diff_mean1 = *(actual_ptr - 3) - mean_actual;
    double diff_mean2 = *(actual_ptr - 2) - mean_actual;
    double diff_mean3 = *(actual_ptr - 1) - mean_actual;

    denominator += w0 * diff_mean0 * diff_mean0 + w1 * diff_mean1 * diff_mean1 + w2 * diff_mean2 * diff_mean2 + w3 * diff_mean3 * diff_mean3;
  }

  for (; i < n; ++i) {
    double w = *(w_ptr++);
    double diff = *(actual_ptr++) - *(predicted_ptr++);
    numerator += w * diff * diff;

    double diff_mean = *(actual_ptr - 1) - mean_actual;
    denominator += w * diff_mean * diff_mean;
  }

  return std::sqrt(numerator / denominator);
}

#endif //REGRESSION_RelativeRootMeanSquaredError_H
