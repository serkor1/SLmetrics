#include "src_Helpers.h"
#include <RcppEigen.h>
#define EIGEN_USE_MKL_ALL
EIGEN_MAKE_ALIGNED_OPERATOR_NEW

inline __attribute__((always_inline)) Rcpp::NumericVector _metric_(const Eigen::MatrixXi& x)
{

  // 1) calcuculate
  // relevent metrics
  const Eigen::ArrayXd& fn = FN(x).cast<double>().array();
  const Eigen::ArrayXd& tn = TN(x).cast<double>().array();

  // 2) return value
  // by class
  return Rcpp::wrap(
    fn / (fn + tn)
  );


}


inline __attribute__((always_inline)) Rcpp::NumericVector _metric_(const Eigen::MatrixXi& x, const bool& micro, const bool& na_rm)
{

  // 1) calcuculate
  // relevent metrics
  const Eigen::ArrayXd& fn = FN(x).cast<double>().array();
  const Eigen::ArrayXd& tn = TN(x).cast<double>().array();


  // 2) return
  // micro average
  // and end function
  if (micro) {

    const double& fn_sum = fn.sum();
    const double& tn_sum = tn.sum();

    return Rcpp::wrap(
      (fn_sum + tn_sum == 0) ? NA_REAL : fn_sum / (fn_sum + tn_sum)
    );

  }

  Eigen::ArrayXd outnut = fn / (fn + tn);

  return Rcpp::wrap(
    outnut.isNaN().select(0,outnut).sum() / ((na_rm) ? (outnut.isNaN() == false).count() : outnut.size())
  );

}
