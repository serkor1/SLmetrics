#include "helpers.h"
#include <RcppEigen.h>
#include <cmath>
#define EIGEN_USE_MKL_ALL
EIGEN_MAKE_ALIGNED_OPERATOR_NEW


/*
 * Classwise metric
 */
inline __attribute__((always_inline)) double _metric_(const Eigen::MatrixXi& x)
{
  // Cast the diagonal matrix to double before summing
  double n_correct = x.diagonal().cast<double>().sum();

  // Cast the rowwise and colwise sums before assigning them to double vectors
  Eigen::VectorXd t_sum = x.rowwise().sum().cast<double>();
  Eigen::VectorXd p_sum = x.colwise().sum().cast<double>();

  // Sum the p_sum vector to get the total number of samples
  double n_samples = p_sum.sum(); // No need to cast since p_sum is already double

  // Compute covariance terms
  double cov_ytyp = n_correct * n_samples - t_sum.dot(p_sum);
  double cov_ypyp = n_samples * n_samples - p_sum.squaredNorm();
  double cov_ytyt = n_samples * n_samples - t_sum.squaredNorm();

  // Compute the product of covariances
  double product = cov_ypyp * cov_ytyt;

  // Handle the case where the product is zero
  if (product == 0) {
    return 0.0;
  }

  // Return the final metric value
  return cov_ytyp / std::sqrt(product);
}



