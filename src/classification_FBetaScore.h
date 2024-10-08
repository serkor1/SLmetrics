#include "src_Helpers.h"
#include <RcppEigen.h>
#include <cmath>
#define EIGEN_USE_MKL_ALL
EIGEN_MAKE_ALIGNED_OPERATOR_NEW


/*
 * Classwise fbeta
 * score
 */
inline __attribute__((always_inline)) Rcpp::NumericVector _metric_(const Eigen::MatrixXi& x, const double& beta = 1.0)
{

  /*
   * Calculate precision
   * and recall
   */
  const double& beta_sq = beta * beta;
  const Eigen::ArrayXd& tp = TP(x).cast<double>().array();
  const Eigen::ArrayXd& fp = FP(x).cast<double>().array();
  const Eigen::ArrayXd& fn = FN(x).cast<double>().array();

  // 1) recall
  const Eigen::ArrayXd& recall_obj = tp / (tp + fn);

  // 2) precision
  const Eigen::ArrayXd& precision_obj = tp / (tp + fp);


  return Rcpp::wrap((1 + beta_sq) * (recall_obj*precision_obj) / (beta_sq * precision_obj + recall_obj));


}


inline __attribute__((always_inline)) Rcpp::NumericVector _metric_(const Eigen::MatrixXi& x, const double& beta, const bool& micro, const bool& na_rm)
{

  /*
   * Calculate precision
   * and recall
   */
  const double& beta_sq = beta * beta;
  const Eigen::ArrayXd& tp = TP(x).cast<double>().array();
  const Eigen::ArrayXd& fp = FP(x).cast<double>().array();
  const Eigen::ArrayXd& fn = FN(x).cast<double>().array();

  // 1) recall
  const Eigen::ArrayXd& recall_obj = tp / (tp + fn);

  // 2) precision
  const Eigen::ArrayXd& precision_obj = tp / (tp + fp);


  // 3) micro average
  // calculation
  if (micro) {

    // 3.1) calculate the sum
    // of tp, fp and fn for micro
    // precision and micro recall
    const double& tp_sum = tp.sum();
    const double& fp_sum = fp.sum();
    const double& fn_sum = fn.sum();

    // 3.2) caclculate
    // precision and recall
    const double& precision_sum = tp_sum / (tp_sum + fp_sum);
    const double& recall_sum = tp_sum / (tp_sum + fn_sum);


    // 3.3) return
    // the micro fbeta
    return Rcpp::wrap((recall_sum + precision_sum == 0) ? R_NaReal: (1 + beta_sq) * (recall_sum * precision_sum) / (beta_sq * precision_sum + recall_sum));
  }

  // 4) intermediate sum
  Eigen::ArrayXd output =  (1 + beta_sq) * (recall_obj * precision_obj) / (beta_sq * precision_obj + recall_obj);


  return Rcpp::wrap(output.isNaN().select(0,output).sum() / ((na_rm) ? (output.isNaN() == false).count() : output.size()));



}
