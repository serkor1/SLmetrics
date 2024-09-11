// [[Rcpp::depends(RcppEigen)]]
#include <RcppEigen.h>
#include "helpers.h"
using namespace Rcpp;
//' Cohens \eqn{\kappa}-statistic
//'
//' @description
//'
//' Cohens
//'
//' @usage
//' kappa(
//'   actual,
//'   predicted,
//'   beta = 0
//' )
//'
//' @inheritParams cmatrix
//' @param beta A <[numeric]> value of [length] 1. 0 by default. If set to a value different from zero, the off-diagonal confusion matrix will be penalized.
//'
//'
//' @details
//' This function calculates the penalized kappa statistic as:
//'
//'   \deqn{\kappa = 1 - \frac{n_{disagree}}{n_{chance}}}
//'
//' where \eqn{n_{disagree}} is the weighted disagreement, and
//' \eqn{n_{chance}} is the expected disagreement by chance. The function
//' operates as follows:
//'
//' 1. **Confusion Matrix**: The confusion matrix \eqn{C} is calculated based
//'    on the input vectors \code{actual} and \code{predicted}.
//'
//' 2. **Penalizing Matrix**: A penalizing matrix \eqn{P} is created using
//'    \code{seqmat}, based on the dimensions of the confusion matrix.
//'    The penalizing matrix assigns weights to each element based on the
//'    absolute differences between the row and column indices, raised to the power \eqn{\beta}.
//'    When \eqn{\beta = 0}, the matrix elements corresponding to perfect agreement
//'    (i.e., the diagonal elements) are set to 0, while all other entries are set to 1.
//'    For higher values of \eqn{\beta}, the penalties grow as the absolute difference between the
//'    indices increases, giving greater penalization to more severe misclassifications.
//'
//' 3. **Weighted Disagreement**: The observed weighted disagreement \eqn{n_{disagree}}
//'    is calculated as:
//'    \deqn{n_{disagree} = \sum_{i,j} C(i,j) P(i,j)}
//'    where \eqn{C(i,j)} is the confusion matrix entry at row \eqn{i}, column \eqn{j}, and
//'    \eqn{P(i,j)} is the corresponding penalizing matrix entry.
//'
//' 4. **Expected Agreement**: The expected agreement by chance \eqn{n_{chance}} is
//'    calculated based on the marginal row and column sums:
//'    \deqn{n_{chance} = \sum_{i,j} \frac{R_i C_j}{N} P(i,j)}
//'    where \eqn{R_i} is the sum of row \eqn{i} of the confusion matrix, \eqn{C_j} is the
//'    sum of column \eqn{j}, and \eqn{N} is the total number of observations.
//'
//' The penalized kappa statistic then measures the agreement adjusted for chance,
//' while penalizing different types of misclassifications depending on their severity
//' (as controlled by \eqn{\beta}).
//'
//' @family classification
//'
// [[Rcpp::export]]
double kappa(
    const Rcpp::IntegerVector& actual,
    const Rcpp::IntegerVector& predicted,
    const double& beta = 0) {

  /*
   * Cohens Kappa
   *
   * This function calculates Cohens Kappa with
   * the option of penalizing values away from the diagonal.
   *
   * It implicitly assumes an ordering of values. This has to be
   * made clear in the documentation at a later point.
   *
   * The penalization can be found in the function seqmat in
   * the helper.h file
   *
   * TODO: It seems that pointers is always
   * faster. Can this really be true?
   * Test it at some point.
   *
   */

  // 0) calculate confusion
  // matrix and the penalizing
  // matrix.
  const Eigen::MatrixXi& conf_matrix = confmat(actual, predicted);
  const Eigen::MatrixXi& penalizing_matrix = seqmat(conf_matrix.cols(), beta);

  // 1) extract the dimensions of
  // the confusion matrix
  std::size_t nrow = conf_matrix.rows();
  std::size_t ncol = conf_matrix.cols();

  // 2) Get the total number of observations (full sum)
  double N = 0.0;
  const int* conf_ptr = conf_matrix.data();
  std::size_t n = conf_matrix.size();
  for (std::size_t i = 0; i < n; ++i) {

    N += conf_ptr[i];

  }

  // 2.1) calculate the reciprocal
  // of the sum
  double N_inv = 1.0 / N;

  // 3) Calculate row and column sums (marginals) and apply penalizing matrix
  Eigen::VectorXd row_sum(nrow);
  Eigen::VectorXd col_sum(ncol);
  row_sum.setZero();
  col_sum.setZero();

  const int* penalizing_ptr = penalizing_matrix.data();
  for (std::size_t i = 0; i < nrow; ++i) {

    for (std::size_t j = 0; j < ncol; ++j) {

      row_sum[i] += conf_matrix(i, j);
      col_sum[j] += conf_matrix(i, j);

    }

  }

  // 4) Calculate weighted disagreement (observed agreement with penalizing matrix)
  double n_disagree = 0.0;
  for (std::size_t i = 0; i < nrow; ++i) {

    for (std::size_t j = 0; j < ncol; ++j) {
      n_disagree += conf_matrix(i, j) * penalizing_matrix(i, j);
    }

  }

  // 5) Calculate expected agreement by chance (weighted)
  double n_chance = 0.0;
  for (std::size_t i = 0; i < nrow; ++i) {

    for (std::size_t j = 0; j < ncol; ++j) {
      n_chance += (row_sum[i] * col_sum[j]) * N_inv * penalizing_matrix(i, j);
    }

  }

  // 6) Return penalized kappa statistic
  return 1.0 - (n_disagree / n_chance);
}
