// [[Rcpp::depends(RcppEigen)]]
#include <RcppEigen.h>
#include "helpers.h"
using namespace Rcpp;

/*
 * These function serves as helper files
 * for {SLmetric} internals.
 *
 * But it doesnt compile if
 * I add in the .h file
 * (Maybe because they aint functions)
 *
 * Internally called _foo_ and exported
 * as .foo
 *
 */


// [[Rcpp::export(".accuracy")]]
double _accuracy_(const Eigen::MatrixXi& x)
{
  // 0) cast to double
  // for operations
  Eigen::MatrixXd xd = x.cast<double>();

  // 1) return without
  // intermediate steps
  return xd.diagonal().sum() / xd.sum();
}

// [[Rcpp::export(".baccuracy")]]
double _baccuracy_(const Eigen::MatrixXi& x, bool adjust = false)
{
  // 0) cast to double
  // for operations
  Eigen::MatrixXd xd = x.cast<double>();

  // 1) construct variables
  // as vectors
  Eigen::VectorXd row_sums = xd.rowwise().sum();
  Eigen::VectorXd diag_vals = xd.diagonal();
  Eigen::VectorXd ratio = diag_vals.array() / row_sums.array();

  // 3) Loop through all values in the ratio vector
  double sum_finite = 0.0;
  int count_finite = 0;

  for (int i = 0; i < ratio.size(); ++i) {
    if (std::isfinite(ratio(i))) {  // Check if the value is finite
      sum_finite += ratio(i);  // Accumulate sum
      count_finite++;  // Increment finite value count
    }
  }

  // 5) Calculate the balanced accuracy (mean of valid ratios)
  double output = sum_finite / count_finite;

  // 6) Adjust for chance findings if required
  if (adjust && count_finite > 0) {
    double chance = 1.0 / count_finite;
    output = (output - chance) / (1.0 - chance);
  }

  return output;

}



// [[Rcpp::export(".specificity")]]
double _specificity_(const Eigen::MatrixXi& x, const bool& micro)
{

  // 0) calculate
  // FP and TN
  const Eigen::VectorXd& fp  = FP(x).cast<double>().array();
  const Eigen::VectorXd& tn   = TN(x).cast<double>().array();


  if (micro) {

    return  (fp.sum() + tn.sum() == 0) ? R_NaReal : tn.sum() / (tn.sum() + fp.sum());

  } else {

    Eigen::VectorXd output = tn.array() / (tn.array() + fp.array());

    return output.sum() / static_cast<double>(x.rows());

  }

}


// [[Rcpp::export(".precision")]]
double _precision_(const Eigen::MatrixXi& x, const bool& micro) {

  // 0) calculate TP and FN
  Eigen::VectorXd tp = TP(x).cast<double>().array();
  Eigen::VectorXd fp = FP(x).cast<double>().array();

  if (micro) {
    // Micro-averaged precision
    return (tp.sum() + fp.sum() == 0) ? R_NaReal : tp.sum() / (tp.sum() + fp.sum());

  } else {
    // Macro-averaged precision
    Eigen::VectorXd output = tp.array() / (tp.array() + fp.array());
    return output.sum() / static_cast<double>(x.rows());
  }
}
