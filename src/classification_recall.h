#include "helpers.h"
#include <RcppEigen.h>
#include <cmath>
#define EIGEN_USE_MKL_ALL
EIGEN_MAKE_ALIGNED_OPERATOR_NEW

/* classification_recall.h
 *
 * This header file includes programs
 * to calculate the metrics found in classification_recall.cpp
 *
 * There are currently two methods:
 *
 * 1. Matrix: with and without aggregation
 * 2. Vectors: with and without aggregation
 *
 */

// Matrix based methods

// Metric:
//
// input: matrix, and Nullable bool for micro
inline __attribute__((always_inline)) Rcpp::NumericVector _metric_(const Eigen::MatrixXi& x)
{

  /*
   * Calculate the metric based on
   * the confusion matrix.
   *
   * NOTE: The function is very fragile in how
   * you define the vectors.
   */

  // 0) calculate TP and FN
  //
  // was vectorXd
  Eigen::VectorXd tp = TP(x).cast<double>().array();
  Eigen::VectorXd fn = FN(x).cast<double>().array();


  // Default behavior: element-wise recall calculation
  Eigen::ArrayXd output = tp.array() / (tp.array() + fn.array());

  // Return the default recall output
  return Rcpp::wrap(output);
}

inline __attribute__((always_inline)) Rcpp::NumericVector _metric_(const Eigen::MatrixXi& x, const bool& micro)
{

  /*
   * Calculate the metric based on
   * the confusion matrix.
   *
   * NOTE: The function is very fragile in how
   * you define the vectors.
   */

  // 0) calculate TP and FN
  //
  // was vectorXd
  Eigen::VectorXd tp = TP(x).cast<double>().array();
  Eigen::VectorXd fn = FN(x).cast<double>().array();

  if (micro) {

    // Micro-average calculation
    return Rcpp::wrap((tp.sum() + fn.sum() == 0) ? R_NaReal : tp.sum() / (tp.sum() + fn.sum()));


  }

  Eigen::VectorXd output = tp.array() / (tp.array() + fn.array());
  return Rcpp::wrap(output.array().isNaN().select(0,output).sum() / (output.array().isNaN() == false).count());


}


inline __attribute__((always_inline)) Rcpp::NumericVector _metric_(const IntegerVector& actual, const IntegerVector& predicted) {

  const Eigen::MatrixXi& x = confmat(actual, predicted);

  /*
   * Calculate the metric based on
   * the confusion matrix.
   *
   * NOTE: The function is very fragile in how
   * you define the vectors.
   */

  // 0) calculate TP and FN
  //
  // was vectorXd
  Eigen::VectorXd tp = TP(x).cast<double>().array();
  Eigen::VectorXd fn = FN(x).cast<double>().array();


  // Default behavior: element-wise recall calculation
  Eigen::ArrayXd output = tp.array() / (tp.array() + fn.array());

  // Return the default recall output
  return Rcpp::wrap(output);

}

inline __attribute__((always_inline)) Rcpp::NumericVector _metric_(const IntegerVector& actual, const IntegerVector& predicted, const bool& micro) {

  const Eigen::MatrixXi& x = confmat(actual, predicted);

  /*
   * Calculate the metric based on
   * the confusion matrix.
   *
   * NOTE: The function is very fragile in how
   * you define the vectors.
   */

  // 0) calculate TP and FN
  //
  // was vectorXd
  Eigen::VectorXd tp = TP(x).cast<double>().array();
  Eigen::VectorXd fn = FN(x).cast<double>().array();

  // Check if the micro argument is not null and handle accordingly
  if (micro) {

    return Rcpp::wrap((tp.sum() + fn.sum() == 0) ? R_NaReal : tp.sum() / (tp.sum() + fn.sum()));


  }

  Eigen::VectorXd output = tp.array() / (tp.array() + fn.array());
  return Rcpp::wrap(output.array().isNaN().select(0,output).sum() / (output.array().isNaN() == false).count());

}
