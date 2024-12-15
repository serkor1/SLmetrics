#ifndef CLASSIFICATION_COHENS_KAPPA_H
#define CLASSIFICATION_COHENS_KAPPA_H

#include "classification_Helpers.h"
#include <RcppEigen.h>
#define EIGEN_USE_MKL_ALL
EIGEN_MAKE_ALIGNED_OPERATOR_NEW

/*
 * Calculation of Cohen's Kappa statistic
 * This class provides methods to compute the Cohen's Kappa with penalization.
 */
class CohensKappaMetric : public classification {
public:
  Rcpp::NumericVector compute(const Eigen::MatrixXd& matrix, double beta) const override {

    // Step 0: Calculate confusion matrix and penalizing matrix
    Eigen::MatrixXd penalizing_matrix = seqmat(matrix.cols(), beta);

    // Step 1: Total number of observations (full sum)
    double N = matrix.sum();
    double N_inv = 1.0 / N;

    // Step 2: Calculate row and column sums
    Eigen::VectorXd row_sum = matrix.rowwise().sum();
    Eigen::VectorXd col_sum = matrix.colwise().sum();

    // Step 3: Calculate weighted disagreement (observed agreement with penalizing matrix)
    double n_disagree = (matrix.cwiseProduct(penalizing_matrix)).sum();

    // Step 4: Calculate expected agreement by chance (weighted)
    double n_chance = (row_sum * col_sum.transpose() * N_inv).cwiseProduct(penalizing_matrix).sum();

    // Step 5: Return penalized kappa statistic
    double kappa = 1.0 - (n_disagree / n_chance);

    return Rcpp::wrap(kappa);
  }

private:
  inline __attribute__((always_inline)) Eigen::MatrixXd seqmat(int n, double power) const {
    Eigen::MatrixXd mat = Eigen::MatrixXd::Zero(n, n);

    for (int i = 0; i < n; ++i) {
      for (int j = 0; j <= i; ++j) {
        mat(i, j) = std::pow(i - j, power);
        mat(j, i) = mat(i, j); // Ensure symmetry
      }
    }

    if (power == 0) {
      mat.diagonal().setZero();
    }

    return mat;
  }
};

#endif
