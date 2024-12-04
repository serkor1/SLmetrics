#ifndef classification_Accuracy_H
#define classification_Accuracy_H

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
Updated Accuracy:
  - The function now accounts for missing values.
  - The funciton is faster than using NumericVector
*/
inline __attribute__((always_inline)) double _metric_(const std::vector<int>& actual, const std::vector<int>& predicted, bool na_rm) 
{

  // 1) common parameters
  // for the calculation
  const int n = actual.size();
  const int NA_INTEGER = std::numeric_limits<int>::min();
  int correct_count = 0;
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
      correct_count += is_valid && (actual_value == predicted_value);
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
  return valid_count > 0 ? static_cast<double>(correct_count) / valid_count : NAN;

}


// Accuracy: cmatrix
inline __attribute__((always_inline)) double _metric_(const Eigen::MatrixXi& x)
{

  Eigen::MatrixXd xd = x.cast<double>();

  return xd.diagonal().sum() / xd.sum();

}


// Balanced Accuracy: factor
inline __attribute__((always_inline)) double _metric_(const IntegerVector& actual, const IntegerVector& predicted, const bool& adjust)
{

  /*
   * Calculate the balanced accuracy
   * NOTE: This could be incorporated
   * in the accuracy function
   */

  // 0) Generate the
  // confusion matrix and
  // count the number of classes k
  Eigen::MatrixXi c_matrix = confmat(actual, predicted);
  int k = c_matrix.rows();

  // 1) calculate the row sums
  // and extract the diagonal of the
  // matrix
  Eigen::VectorXi row_sums = c_matrix.rowwise().sum();
  Eigen::VectorXi diag = c_matrix.diagonal();

  // 2) class-wise sum
  // and valid_classes
  double per_class_sum = 0.0;
  int valid_classes = 0;

  // 3) loop through
  // valid cases and increment
  // accordingly
  for (int i = 0; i < k; ++i) {

    if (row_sums(i) > 0) {

      per_class_sum += static_cast<double>(diag(i)) / row_sums(i);
      ++valid_classes;

    }

  }

  // 4) calculate balanced accuracy
  // accordingly
  double output = per_class_sum / valid_classes;

  // 5) adjust for chance
  // findings
  if (adjust && valid_classes > 0) {

    double chance = 1.0 / valid_classes;
    output = (output - chance) / (1.0 - chance);

  }

  return output;


}

// Balanced Accuracy: c_matrix
inline __attribute__((always_inline)) double _metric_(const Eigen::MatrixXi& x, const bool& adjust)
{

  /*
   * Calculate the balanced accuracy
   * NOTE: This could be incorporated
   * in the accuracy function
   */

  // 0) Generate the
  // confusion matrix and
  // count the number of classes k
  int k = x.rows();

  // 1) calculate the row sums
  // and extract the diagonal of the
  // matrix
  Eigen::VectorXi row_sums = x.rowwise().sum();
  Eigen::VectorXi diag = x.diagonal();

  // 2) class-wise sum
  // and valid_classes
  double per_class_sum = 0.0;
  int valid_classes = 0;

  // 3) loop through
  // valid cases and increment
  // accordingly
  for (int i = 0; i < k; ++i) {

    if (row_sums(i) > 0) {

      per_class_sum += static_cast<double>(diag(i)) / row_sums(i);
      ++valid_classes;

    }

  }

  // 4) calculate balanced accuracy
  // accordingly
  double output = per_class_sum / valid_classes;

  // 5) adjust for chance
  // findings
  if (adjust && valid_classes > 0) {

    double chance = 1.0 / valid_classes;
    output = (output - chance) / (1.0 - chance);

  }

  return output;


}


#endif