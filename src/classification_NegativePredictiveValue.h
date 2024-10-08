#include "src_Helpers.h"
#include <RcppEigen.h>
#define EIGEN_USE_MKL_ALL
EIGEN_MAKE_ALIGNED_OPERATOR_NEW

inline __attribute__((always_inline)) Rcpp::NumericVector _metric_(const Eigen::MatrixXi& x)
{

  // 1) calcuculate
  // relevent metrics
  const Eigen::ArrayXd& tn = TN(x).cast<double>().array();
  const Eigen::ArrayXd& fn = FN(x).cast<double>().array();

  // 2) return value
  // by class
  return Rcpp::wrap(
    tn / (tn + fn)
  );


}


inline __attribute__((always_inline)) Rcpp::NumericVector _metric_(const Eigen::MatrixXi& x, const bool& micro, const bool& na_rm)
{

  // 1) calcuculate
  // relevent metrics
  const Eigen::ArrayXd& tn = TN(x).cast<double>().array();
  const Eigen::ArrayXd& fn = FN(x).cast<double>().array();

  // 2) return
  // micro average
  // and end function
  if (micro) {

    const double& tn_sum = tn.sum();
    const double& fn_sum = fn.sum();

    return Rcpp::wrap(
      (tn_sum + fn_sum == 0) ? NA_REAL : tn_sum / (tn_sum + fn_sum)
    );

  }

  Eigen::ArrayXd output = tn / (tn + fn);

  return Rcpp::wrap(
    output.isNaN().select(0,output).sum() / ((na_rm) ? (output.isNaN() == false).count() : output.size())
  );

}
