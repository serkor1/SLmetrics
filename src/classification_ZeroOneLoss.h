#ifndef classification_ZeroOneLoss_H
#define classification_ZeroOneLoss_H

/*
 * This header file is for calculating
 * accucracy and balanced accuracy
 */
#include "src_Helpers.h"
#include <RcppEigen.h>
#include <cmath>
#include <vector>
#include <limits>
#define EIGEN_USE_MKL_ALL
EIGEN_MAKE_ALIGNED_OPERATOR_NEW



/*
 * Zero One Loss; factors
 */
inline __attribute__((always_inline)) double _metric_(const std::vector<int>& actual, const std::vector<int>& predicted, bool na_rm)
{

  // 1) common parameters
  // for the calculation
  const int n = actual.size();
  const int NA_INTEGER = std::numeric_limits<int>::min();
  int incorrect_count = 0;
  int valid_count = 0;

  
  // 2) loop through the values
  // using pointers
  for (int i = 0; i < n; ++i) {
      const int actual_value = actual[i];
      const int predicted_value = predicted[i];

      // 2.1) check for non-NA values
      const bool is_valid = actual_value != NA_INTEGER && predicted_value != NA_INTEGER;
      valid_count += is_valid;

      // 2.2) increment correct count if valid and equal
      incorrect_count += is_valid && (actual_value != predicted_value);
  }

  // 3) if there is missing values
  // return NAN
  // NOTE: Maybe this more efficient to have inside
  // the loop and stop it early
  if (!na_rm && valid_count != n) {
      return NAN;
  }

  // 4) return values
  // if valid_count is above
  // 0.
  return valid_count > 0 ? static_cast<double>(incorrect_count) / valid_count : NAN;


}


/*
 * Zero One Loss; cmatrix
 */
inline __attribute__((always_inline)) double _metric_(const Eigen::MatrixXi& x)
{

  // 1) extract total
  // N and True Positives Sum
  int N = x.sum();
  int TP = x.diagonal().sum();

  // 2) return value
  return static_cast<double>(N - TP) / N;

}

#endif