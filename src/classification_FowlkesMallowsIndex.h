#include "src_Helpers.h"
#include <RcppEigen.h>
#define EIGEN_USE_MKL_ALL
EIGEN_MAKE_ALIGNED_OPERATOR_NEW


/*
 * Calculation of the Fawlks Mallows
 * Index follows that of https://en.wikipedia.org/wiki/Fowlkes%E2%80%93Mallows_index
 * for any specific value k.
 *
 * Using the sqrt(PPV * TPR)-approach directly yields
 * a different result than scikit-learn.Hence this approach
 * is prefferred
 */
inline __attribute__((always_inline)) double _metric_(const Eigen::MatrixXi& x)
{
  // Dimensions and sum of matrix
  double N = x.sum();
  int k = x.rows();

  // Calculate tk, pk, and qk without copying x
  double tk = x.cast<double>().array().square().sum();

  Eigen::VectorXd rowSums = x.cast<double>().rowwise().sum();
  Eigen::VectorXd colSums = x.cast<double>().colwise().sum();

  double pk = colSums.squaredNorm();
  double qk = rowSums.squaredNorm();

  // Adjust tk, pk, and qk by subtracting N
  tk -= N;
  pk -= N;
  qk -= N;

  // Check for non-positive values to avoid division by zero or negative roots
  if (tk <= 0 || pk <= 0 || qk <= 0) {
    return 0.0;
  }

  // Return the Fowlkes-Mallows Index calculation
  return std::sqrt(tk * tk / (pk * qk));
}
