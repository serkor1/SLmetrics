#include "helpers.h"
#include <RcppEigen.h>
#include <cmath>
#define EIGEN_USE_MKL_ALL
EIGEN_MAKE_ALIGNED_OPERATOR_NEW


/*
 * Classwise fpr
 */
inline __attribute__((always_inline)) Rcpp::NumericVector _metric_(const Eigen::MatrixXi& x)
{

  // 1) calcuculate
  // relevent metrics
  const Eigen::ArrayXd& fp = FP(x).cast<double>().array();
  const Eigen::ArrayXd& tn = TN(x).cast<double>().array();

  // 2) return value
  // by class
  return Rcpp::wrap(
    fp / (fp + tn)
  );


}


inline __attribute__((always_inline)) Rcpp::NumericVector _metric_(const Eigen::MatrixXi& x, const bool& micro, const bool& na_rm)
{

  // 1) calcuculate
  // relevent metrics
  const Eigen::ArrayXd& fp = FP(x).cast<double>().array();
  const Eigen::ArrayXd& tn = TN(x).cast<double>().array();

  // 2) return
  // micro average
  // and end function
  if (micro) {

    const double& fp_sum = fp.sum();
    const double& tn_sum = tn.sum();

    return Rcpp::wrap(
      (fp_sum + tn_sum == 0) ? NA_REAL : fp_sum / (fp_sum + tn_sum)
    );

  }

  Eigen::ArrayXd output =  fp / (fp + tn);

  return Rcpp::wrap(
    output.isNaN().select(0,output).sum() / ((na_rm) ? (output.isNaN() == false).count() : output.size())
    );

}
