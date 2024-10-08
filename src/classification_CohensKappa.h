#include "src_Helpers.h"
#include <RcppEigen.h>
#include <cmath>
#define EIGEN_USE_MKL_ALL
EIGEN_MAKE_ALIGNED_OPERATOR_NEW

inline __attribute__((always_inline)) double _metric_(const Eigen::MatrixXi& x, const double& beta)
{

  // Step 0: Calculate confusion matrix and penalizing matrix
  const Eigen::MatrixXi& penalizing_matrix = seqmat(x.cols(), beta);

  // Step 1: Extract dimensions of the confusion matrix
  std::size_t nrow = x.rows();
  std::size_t ncol = x.cols();

  // Step 2: Total number of observations (full sum)
  double N = x.sum();
  double N_inv = 1.0 / N;

  // Step 3: Calculate row and column sums
  Eigen::VectorXd row_sum = x.rowwise().sum().cast<double>();
  Eigen::VectorXd col_sum = x.colwise().sum().cast<double>();

  // Step 4: Calculate weighted disagreement (observed agreement with penalizing matrix)
  double n_disagree = (x.cast<double>().cwiseProduct(penalizing_matrix.cast<double>())).sum();

  // Step 5: Calculate expected agreement by chance (weighted)
  double n_chance = (row_sum * col_sum.transpose() * N_inv).cwiseProduct(penalizing_matrix.cast<double>()).sum();

  // Step 6: Return penalized kappa statistic
  return 1.0 - (n_disagree / n_chance);


}
