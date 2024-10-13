#ifndef REGRESSION_D2PINBALLLOSS_H
#define REGRESSION_D2PINBALLLOSS_H

#include <Rcpp.h>
#include <cmath>
#include <numeric>
using namespace Rcpp;

// Weighted version of pinball loss
inline __attribute__((always_inline)) double _metric_(const NumericVector& actual, const NumericVector& predicted, const NumericVector& w, const double& alpha = 0.5) {
  const std::size_t n = actual.size();

  const double* actual_ptr = actual.begin();
  const double* predicted_ptr = predicted.begin();
  const double* weight_ptr = w.begin();

  double loss = 0.0;
  double weight_sum = 0.0;
  int i = 0;
  int limit = n - (n % 4);

  for (; i < limit; i += 4) {
    double diff0 = *(actual_ptr++) - *(predicted_ptr++);
    double diff1 = *(actual_ptr++) - *(predicted_ptr++);
    double diff2 = *(actual_ptr++) - *(predicted_ptr++);
    double diff3 = *(actual_ptr++) - *(predicted_ptr++);

    double sign0 = (diff0 >= 0) ? 1.0 : 0.0;
    double sign1 = (diff1 >= 0) ? 1.0 : 0.0;
    double sign2 = (diff2 >= 0) ? 1.0 : 0.0;
    double sign3 = (diff3 >= 0) ? 1.0 : 0.0;

    double weight0 = *(weight_ptr++);
    double weight1 = *(weight_ptr++);
    double weight2 = *(weight_ptr++);
    double weight3 = *(weight_ptr++);

    loss += weight0 * (alpha * sign0 * diff0 - (1 - alpha) * (1 - sign0) * diff0);
    loss += weight1 * (alpha * sign1 * diff1 - (1 - alpha) * (1 - sign1) * diff1);
    loss += weight2 * (alpha * sign2 * diff2 - (1 - alpha) * (1 - sign2) * diff2);
    loss += weight3 * (alpha * sign3 * diff3 - (1 - alpha) * (1 - sign3) * diff3);

    weight_sum += weight0 + weight1 + weight2 + weight3;
  }

  for (; i < n; ++i) {
    double diff = *(actual_ptr++) - *(predicted_ptr++);
    double sign = (diff >= 0) ? 1.0 : 0.0;
    double weight = *(weight_ptr++);

    loss += weight * (alpha * sign * diff - (1 - alpha) * (1 - sign) * diff);
    weight_sum += weight;
  }

  return weight_sum > 0 ? (loss / weight_sum) : 0.0;
}

// Unweighted version of pinball loss
inline __attribute__((always_inline)) double _metric_(const NumericVector& actual, const NumericVector& predicted, const double& alpha = 0.5) {
  const std::size_t n = actual.size();

  const double* actual_ptr = actual.begin();
  const double* predicted_ptr = predicted.begin();

  double loss = 0.0;
  int i = 0;
  int limit = n - (n % 4);

  for (; i < limit; i += 4) {
    double diff0 = *(actual_ptr++) - *(predicted_ptr++);
    double diff1 = *(actual_ptr++) - *(predicted_ptr++);
    double diff2 = *(actual_ptr++) - *(predicted_ptr++);
    double diff3 = *(actual_ptr++) - *(predicted_ptr++);

    double sign0 = (diff0 >= 0) ? 1.0 : 0.0;
    double sign1 = (diff1 >= 0) ? 1.0 : 0.0;
    double sign2 = (diff2 >= 0) ? 1.0 : 0.0;
    double sign3 = (diff3 >= 0) ? 1.0 : 0.0;

    loss += alpha * sign0 * diff0 - (1 - alpha) * (1 - sign0) * diff0;
    loss += alpha * sign1 * diff1 - (1 - alpha) * (1 - sign1) * diff1;
    loss += alpha * sign2 * diff2 - (1 - alpha) * (1 - sign2) * diff2;
    loss += alpha * sign3 * diff3 - (1 - alpha) * (1 - sign3) * diff3;
  }

  for (; i < n; ++i) {
    double diff = *(actual_ptr++) - *(predicted_ptr++);
    double sign = (diff >= 0) ? 1.0 : 0.0;

    loss += alpha * sign * diff - (1 - alpha) * (1 - sign) * diff;
  }

  return loss / n;
}

#endif // REGRESSION_D2PINBALLLOSS_H
