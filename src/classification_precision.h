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

  // 0) calculate TP and FP
  //
  // was ArrayXd
  Eigen::ArrayXd tp = TP(x).cast<double>();
  Eigen::ArrayXd fp = FP(x).cast<double>();


  // Default behavior: element-wise recall calculation
  Eigen::ArrayXd output = tp / (tp + fp);

  // Return the default recall output
  return Rcpp::wrap(output);
}

inline __attribute__((always_inline)) Rcpp::NumericVector _metric_(const Eigen::MatrixXi& x, const bool& micro, const bool& na_rm)
{

  /*
   * Calculate the metric based on
   * the confusion matrix.
   *
   * NOTE: The function is very fragile in how
   * you define the vectors.
   */

  // 0) calculate TP and FP
  //
  // was ArrayXd
  Eigen::ArrayXd tp = TP(x).cast<double>().array();
  Eigen::ArrayXd fp = FP(x).cast<double>().array();

  if (micro) {

    // Micro-average calculation
    return Rcpp::wrap((tp.sum() + fp.sum() == 0) ? R_NaReal : tp.sum() / (tp.sum() + fp.sum()));


  }

  Eigen::ArrayXd output = tp / (tp + fp);
  return Rcpp::wrap(output.isNaN().select(0,output).sum() /((na_rm) ? (output.isNaN() == false).count() : output.size()));


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

  // 0) calculate TP and FP
  //
  // was ArrayXd
  Eigen::ArrayXd tp = TP(x).cast<double>().array();
  Eigen::ArrayXd fp = FP(x).cast<double>().array();


  // Default behavior: element-wise recall calculation
  Eigen::ArrayXd output = tp / (tp + fp);

  // Return the default recall output
  return Rcpp::wrap(output);

}

inline __attribute__((always_inline)) Rcpp::NumericVector _metric_(const IntegerVector& actual, const IntegerVector& predicted, const bool& micro, const bool& na_rm) {

  const Eigen::MatrixXi& x = confmat(actual, predicted);

  /*
   * Calculate the metric based on
   * the confusion matrix.
   *
   * NOTE: The function is very fragile in how
   * you define the vectors.
   */

  // 0) calculate TP and FP
  //
  // was ArrayXd
  Eigen::ArrayXd tp = TP(x).cast<double>().array();
  Eigen::ArrayXd fp = FP(x).cast<double>().array();

  // Check if the micro argument is not null and handle accordingly
  if (micro) {

    return Rcpp::wrap((tp.sum() + fp.sum() == 0) ? R_NaReal : tp.sum() / (tp.sum() + fp.sum()));


  }

  Eigen::ArrayXd output = tp / (tp + fp);
  return Rcpp::wrap(output.isNaN().select(0,output).sum() / ((na_rm) ? (output.isNaN() == false).count() : output.size()));

}
