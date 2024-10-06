#include "helpers.h"
#include <RcppEigen.h>
#include <cmath>
#define EIGEN_USE_MKL_ALL
EIGEN_MAKE_ALIGNED_OPERATOR_NEW


/*
 * Classwise metric
 */
inline __attribute__((always_inline)) Rcpp::NumericVector _metric_(const Eigen::MatrixXi& x)
{

  /*
   * Extract
   */
  const Eigen::ArrayXd& tp = TP(x).cast<double>().array();
  const Eigen::ArrayXd& fp = FP(x).cast<double>().array();
  const Eigen::ArrayXd& fn = FN(x).cast<double>().array();

  return Rcpp::wrap(
    tp / (tp + fp + fn)
  );

}


inline __attribute__((always_inline)) Rcpp::NumericVector _metric_(const Eigen::MatrixXi& x, const bool& micro, const bool& na_rm)
{

  /*
   * Extract
   */
  const Eigen::ArrayXd& tp = TP(x).cast<double>().array();
  const Eigen::ArrayXd& fp = FP(x).cast<double>().array();
  const Eigen::ArrayXd& fn = FN(x).cast<double>().array();


  if (micro) {


    const double& tp_sum = tp.sum();
    const double& fp_sum = fp.sum();
    const double& fn_sum = fn.sum();


    return Rcpp::wrap(
      tp_sum / (tp_sum + fp_sum + fn_sum)
    );

  }


  const Eigen::ArrayXd& output = tp / (tp + fp + fn);

  return Rcpp::wrap(output.isNaN().select(0,output).sum() / ((na_rm) ? (output.isNaN() == false).count() : output.size()));



}
