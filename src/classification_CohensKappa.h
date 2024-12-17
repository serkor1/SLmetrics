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

    // 0) initialize containers
    Eigen::MatrixXd penalizing_matrix(matrix.cols(), matrix.cols());
    Eigen::VectorXd row_sum(matrix.cols()), col_sum(matrix.cols());

    // 1) populate the 
    // matrix
    penalizing_matrix = penalizingMatrix(matrix.cols(), beta);

    // 2) 
    double N = matrix.sum();
    double N_inv = 1.0 / N;

    // 3)
    row_sum = matrix.rowwise().sum();
    col_sum = matrix.colwise().sum();

    // 4) Calculate weighted disagreement (observed agreement with penalizing matrix)
    double n_disagree = (matrix.cwiseProduct(penalizing_matrix)).sum();

    // 5) Calculate expected agreement by chance (weighted)
    double n_chance = (row_sum * col_sum.transpose() * N_inv).cwiseProduct(penalizing_matrix).sum();

    // Step 5: Return penalized kappa statistic
    double kappa = 1.0 - (n_disagree / n_chance);

    return Rcpp::wrap(kappa);

  }

private:

  inline __attribute__((always_inline)) Eigen::MatrixXd penalizingMatrix(const int& n, const double& power) const {
    
    /*
    Returns a diagonal matrix, with diag(0)      
    */
    
    Eigen::MatrixXd matrix(n, n);
    
    double* mat_data = matrix.data();

    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) { 
            double value = std::pow(std::abs(j - i), power);

            double* upper_elem = mat_data + i * n + j;
            double* lower_elem = mat_data + j * n + i;
            double* diag_elem  = mat_data + i * n + i;

            *upper_elem = value;
            *lower_elem = value;
            *diag_elem  = 0.0;
        }
    }

    return matrix;

  }

};

#endif
