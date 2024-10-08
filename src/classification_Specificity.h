#include "src_Helpers.h"
#include <RcppEigen.h>
#include <cmath>
#define EIGEN_USE_MKL_ALL
EIGEN_MAKE_ALIGNED_OPERATOR_NEW


/*
 * Class-wise specificity
 */
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
  Eigen::ArrayXd fp = FP(x).cast<double>().array();
  Eigen::ArrayXd tn = TN(x).cast<double>().array();


  // Default behavior: element-wise recall calculation
  Eigen::ArrayXd output = tn / (fp + tn);

  // Return the default recall output
  return Rcpp::wrap(output);
}

/*
 * Aggregated specificity
 */

inline __attribute__((always_inline)) Rcpp::NumericVector _metric_(const Eigen::MatrixXi& x, const bool& micro, const bool& na_rm) {

  /*
   * Calculate the metric based on
   * the confusion matrix.
   *
   * NOTE: The function is very fragile in how
   * you define the vectors.
   */

  // 0) calculate TP and FP
  //
  // was vectorXd
  Eigen::ArrayXd fp = FP(x).cast<double>().array();
  Eigen::ArrayXd tn = TN(x).cast<double>().array();

  // Check if the micro argument is not null and handle accordingly
  if (micro) {

    return Rcpp::wrap((fp.sum() + tn.sum() == 0) ? R_NaReal : tn.sum() / (fp.sum() + tn.sum()));


  }

  Eigen::ArrayXd output = tn / (fp + tn);
  return Rcpp::wrap(output.isNaN().select(0,output).sum() / ((na_rm) ? (output.isNaN() == false).count() : output.size()));

}
