#include "src_Helpers.h"
#include <RcppEigen.h>
#include <cmath>
#define EIGEN_USE_MKL_ALL
EIGEN_MAKE_ALIGNED_OPERATOR_NEW


/*
 * Classwise plr
 */
inline __attribute__((always_inline)) Rcpp::NumericVector _metric_(const Eigen::MatrixXi& x)
{

  /*
   * Extract
   */
  const Eigen::ArrayXd& tp = TP(x).cast<double>().array();
  const Eigen::ArrayXd& fp = FP(x).cast<double>().array();
  const Eigen::ArrayXd& fn = FN(x).cast<double>().array();
  const Eigen::ArrayXd& tn = TN(x).cast<double>().array();

  return Rcpp::wrap(
    (tp / (tp + fn)) / (1.0 - (tn / (tn + fp)))
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
  const Eigen::ArrayXd& tn = TN(x).cast<double>().array();


  if (micro) {


    const double& tp_sum = tp.sum();
    const double& fp_sum = fp.sum();
    const double& fn_sum = fn.sum();
    const double& tn_sum = tn.sum();


    return Rcpp::wrap(
      (tp_sum/(tp_sum + fn_sum)) / (1.0 - (tn_sum / (tn_sum + fp_sum)))
    );

  }


  const Eigen::ArrayXd& output = (tp/(tp + fn)) / (1.0 - (tn / (tn + fp)));

  return Rcpp::wrap(output.isNaN().select(0,output).sum() / ((na_rm) ? (output.isNaN() == false).count() : output.size()));



}
