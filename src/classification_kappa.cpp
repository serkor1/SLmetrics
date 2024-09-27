// [[Rcpp::depends(RcppEigen)]]
#include <RcppEigen.h>
#include "helpers.h"
using namespace Rcpp;
//' Compute Cohen's \eqn{\kappa}-statistic
//'
//' @description
//' The [kappa()]-function computes [Cohen's \eqn{\kappa}](https://en.wikipedia.org/wiki/Cohen%27s_kappa), a statistic that measures inter-rater agreement for categorical items between
//' two vectors of predicted and observed [factor()] values.
//'
//' If \eqn{\beta \neq 0} the off-diagonals of the confusion matrix are penalized with a factor of
//' \eqn{(y_{+} - y_{i,-})^\beta}. See below for further details.
//'
//' @usage
//' kappa(
//'   actual,
//'   predicted,
//'   beta = 0
//' )
//'
//' @example man/examples/scr_kappa.R
//'
//' @inherit specificity
//'
//' @inheritParams specificity
//' @param beta A <[numeric]> value of [length] 1. 0 by default. If set to a value different from zero, the off-diagonal confusion matrix will be penalized.
//'
//'
//' @section Calculation
//'
//'
//'
//' @family classification
//' @export
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
