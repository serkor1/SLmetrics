#ifndef REGRESSION_MEANPERCENTAGEERROR_H
#define REGRESSION_MEANPERCENTAGEERROR_H


#include <Rcpp.h>
#include <cmath>
using namespace Rcpp;

// Unweighted MPE Calculation
inline __attribute__((always_inline)) double _metric_(const NumericVector& actual, const NumericVector& predicted)
{
  const std::size_t n = actual.size();
  double output = 0.0;

  const double* actual_ptr = actual.begin();
  const double* predicted_ptr = predicted.begin();

  int i = 0;
  int limit = n - (n % 4);

  for (; i < limit; i += 4) {
    double percentage_error0 = (actual_ptr[i] - predicted_ptr[i]) / actual_ptr[i];
    double percentage_error1 = (actual_ptr[i + 1] - predicted_ptr[i + 1]) / actual_ptr[i + 1];
    double percentage_error2 = (actual_ptr[i + 2] - predicted_ptr[i + 2]) / actual_ptr[i + 2];
    double percentage_error3 = (actual_ptr[i + 3] - predicted_ptr[i + 3]) / actual_ptr[i + 3];

    output += percentage_error0 + percentage_error1 + percentage_error2 + percentage_error3;
  }

  for (; i < n; ++i) {
    double percentage_error = (actual_ptr[i] - predicted_ptr[i]) / actual_ptr[i];
    output += percentage_error;
  }

  return output / n;
}

// Weighted MPE Calculation
inline __attribute__((always_inline)) double _metric_(const NumericVector& actual, const NumericVector& predicted, const NumericVector& w)
{
  const std::size_t n = actual.size();
  double numerator = 0.0;
  double denominator = 0.0;

  const double* actual_ptr = actual.begin();
  const double* predicted_ptr = predicted.begin();
  const double* w_ptr = w.begin();

  int i = 0;
  int limit = n - (n % 4);

  for (; i < limit; i += 4) {
    double percentage_error0 = (actual_ptr[i] - predicted_ptr[i]) / actual_ptr[i];
    double weight0 = w_ptr[i];

    double percentage_error1 = (actual_ptr[i + 1] - predicted_ptr[i + 1]) / actual_ptr[i + 1];
    double weight1 = w_ptr[i + 1];

    double percentage_error2 = (actual_ptr[i + 2] - predicted_ptr[i + 2]) / actual_ptr[i + 2];
    double weight2 = w_ptr[i + 2];

    double percentage_error3 = (actual_ptr[i + 3] - predicted_ptr[i + 3]) / actual_ptr[i + 3];
    double weight3 = w_ptr[i + 3];

    numerator += (percentage_error0 * weight0);
    numerator += (percentage_error1 * weight1);
    numerator += (percentage_error2 * weight2);
    numerator += (percentage_error3 * weight3);

    denominator += weight0 + weight1 + weight2 + weight3;
  }

  for (; i < n; ++i) {
    double percentage_error = (actual_ptr[i] - predicted_ptr[i]) / actual_ptr[i];
    double weight = w_ptr[i];
    numerator += (percentage_error * weight);
    denominator += weight;
  }

  return numerator / denominator;
}

#endif //REGRESSION_MEANPERCENTAGEERROR_H
