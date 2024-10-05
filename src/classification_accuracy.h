/*
 * This header file is for calculating
 * accucracy and balanced accuracy
 */
#include "helpers.h"
#include <RcppEigen.h>
#include <cmath>
#define EIGEN_USE_MKL_ALL
EIGEN_MAKE_ALIGNED_OPERATOR_NEW


// Accuracy: factor
inline __attribute__((always_inline)) double _metric_(const NumericVector& actual, const NumericVector& predicted)
{

  const int n = actual.size();

  const double* actual_ptr = actual.begin();
  const double* predicted_ptr = predicted.begin();

  int correct_count = 0;

  for (int i = 0; i < n; ++i) {

    correct_count += (*(actual_ptr++) == *(predicted_ptr++));

  }

  return static_cast<double> (correct_count) / n;

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
