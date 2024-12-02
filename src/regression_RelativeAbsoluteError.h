#ifndef REGRESSION_RelativeAbsoluteError_H
#define REGRESSION_RelativeAbsoluteError_H
#include <Rcpp.h>
#include <cmath>
#include <numeric>
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
    double diff0 = std::abs(*(actual_ptr++) - *(predicted_ptr++));
    double diff1 = std::abs(*(actual_ptr++) - *(predicted_ptr++));
    double diff2 = std::abs(*(actual_ptr++) - *(predicted_ptr++));
    double diff3 = std::abs(*(actual_ptr++) - *(predicted_ptr++));

    numerator += diff0 + diff1 + diff2 + diff3;

    double diff_mean0 = std::abs(*(actual_ptr - 4) - mean_actual);
    double diff_mean1 = std::abs(*(actual_ptr - 3) - mean_actual);
    double diff_mean2 = std::abs(*(actual_ptr - 2) - mean_actual);
    double diff_mean3 = std::abs(*(actual_ptr - 1) - mean_actual);

    denominator += diff_mean0 + diff_mean1 + diff_mean2 + diff_mean3;
  }

  for (; i < n; ++i) {
    double diff = std::abs(*(actual_ptr++) - *(predicted_ptr++));
    numerator += diff;

    double diff_mean = std::abs(*(actual_ptr - 1) - mean_actual);
    denominator += diff_mean;
  }

  return numerator / denominator;
}


inline __attribute__((always_inline)) double _metric_(const NumericVector& actual, const NumericVector& predicted, const NumericVector& w)
{
  const std::size_t n = actual.size();
  const double weighted_sum = std::accumulate(w.begin(), w.end(), 0.0);
  const double mean_actual = std::inner_product(actual.begin(), actual.end(), w.begin(), 0.0) / weighted_sum;

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

    double diff0 = std::abs(*(actual_ptr++) - *(predicted_ptr++));
    double diff1 = std::abs(*(actual_ptr++) - *(predicted_ptr++));
    double diff2 = std::abs(*(actual_ptr++) - *(predicted_ptr++));
    double diff3 = std::abs(*(actual_ptr++) - *(predicted_ptr++));

    numerator += w0 * diff0 + w1 * diff1 + w2 * diff2 + w3 * diff3;

    double diff_mean0 = std::abs(*(actual_ptr - 4) - mean_actual);
    double diff_mean1 = std::abs(*(actual_ptr - 3) - mean_actual);
    double diff_mean2 = std::abs(*(actual_ptr - 2) - mean_actual);
    double diff_mean3 = std::abs(*(actual_ptr - 1) - mean_actual);

    denominator += w0 * diff_mean0 + w1 * diff_mean1 + w2 * diff_mean2 + w3 * diff_mean3;
  }

  for (; i < n; ++i) {
    double w = *(w_ptr++);
    double diff = std::abs(*(actual_ptr++) - *(predicted_ptr++));
    numerator += w * diff;

    double diff_mean = std::abs(*(actual_ptr - 1) - mean_actual);
    denominator += w * diff_mean;
  }

  return numerator / denominator;
}

#endif //REGRESSION_RelativeAbsoluteError_H
