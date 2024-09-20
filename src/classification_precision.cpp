// [[Rcpp::depends(RcppEigen)]]
#include <RcppEigen.h>
#include "helpers.h"
using namespace Rcpp;

//' Precision (Positive Predictive Value)
//'
//'
//' @description
//' Calculate the Precision
//'
//' @usage
//' # 1) `precision()`-function
//' precision(
//'   actual,
//'   predicted,
//'   aggregate = FALSE
//' )
//'
//' @inherit specificity
//'
//' @details
//'
//' The Precision (Positive Predictive Value, PPV) is calculated for each class \eqn{k} as follows,
//'
//' \deqn{
//'   \frac{\#TP_k}{\#TP_k + \#FP_k}
//' }
//'
//' Where \eqn{\#TP_k} and \eqn{\#FP_k} are the number of true positives and false positives, respectively, for each class \eqn{k}.
//'
//' When `aggregate = TRUE`, the `micro`-average is calculated,
//'
//' \deqn{
//'   \frac{\sum_{k=1}^k \#TP_k}{\sum_{k=1}^k \#TP_k + \sum_{k=1}^k \#FP_k}
//' }
//'
//' @example man/examples/scr_precision.R
//'
//' @returns
//' A named <[numeric]> vector of length k
//'
//'
//' @family classification
//'
//' @export
// [[Rcpp::export]]
NumericVector precision(
    const IntegerVector& actual,
    const IntegerVector& predicted,
    const bool& aggregate = false) {

  /*
   * Calculate:
   *
   * 1) Confusion Matrix
   * 2) True Positives
   * 3) False Positive
   *
   * Output is precision
   */

  // 0) calculate the
  // confusion matrix, TP and FP
  const Eigen::MatrixXi& c_matrix        = confmat(actual, predicted);
  const Eigen::VectorXi& true_positive   = TP(c_matrix);
  const Eigen::VectorXi& false_positive  = FP(c_matrix);

  // 1) caste the integer vectors
  // to double arrays
  const Eigen::ArrayXd& tp_dbl = true_positive.cast<double>().array();
  const Eigen::ArrayXd& fp_dbl = false_positive.cast<double>().array();

  // 2) declare output
  // vector
  Rcpp::NumericVector output;

  if (aggregate) {

    const double tp = tp_dbl.sum();
    const double fn = fp_dbl.sum();

    output = Rcpp::NumericVector::create(tp / (tp + fn));

  } else {

    // 0) calculate length
    // of the vector to avoid
    // dynamic allocation of vector
    // sizes.
    const int n = tp_dbl.size();
    output = Rcpp::NumericVector(n);

    // 1) Get raw pointers to the data for faster access
    const double* tp_ptr = tp_dbl.data();
    const double* fp_ptr = fp_dbl.data();
    double* output_ptr = REAL(output);

    // 2) Use a pointer-based loop to calculate recall (TPR) element-wise
    for (int i = 0; i < n; ++i) {
      output_ptr[i] = tp_ptr[i] / (tp_ptr[i] + fp_ptr[i]);
    }

    // Set names attribute using reference
    output.attr("names") = actual.attr("levels");

  }

  return output;
}

//' @rdname precision
//'
//'
//' @usage
//' # 2) `ppv()`-function
//' ppv(
//'   actual,
//'   predicted,
//'   aggregate = FALSE
//' )
//'
// [[Rcpp::export]]
NumericVector ppv(
    const IntegerVector& actual,
    const IntegerVector& predicted,
    const bool& aggregate = false) {

  /*
   * Calculate:
   *
   * 1) Confusion Matrix
   * 2) True Positives
   * 3) False Positive
   *
   * Output is precision
   */

  // 0) calculate the
  // confusion matrix, TP and FP
  const Eigen::MatrixXi& c_matrix        = confmat(actual, predicted);
  const Eigen::VectorXi& true_positive   = TP(c_matrix);
  const Eigen::VectorXi& false_positive  = FP(c_matrix);

  // 1) caste the integer vectors
  // to double arrays
  const Eigen::ArrayXd& tp_dbl = true_positive.cast<double>().array();
  const Eigen::ArrayXd& fp_dbl = false_positive.cast<double>().array();

  // 2) declare output
  // vector
  Rcpp::NumericVector output;

  if (aggregate) {

    const double tp = tp_dbl.sum();
    const double fn = fp_dbl.sum();

    output = Rcpp::NumericVector::create(tp / (tp + fn));

  } else {

    // 0) calculate length
    // of the vector to avoid
    // dynamic allocation of vector
    // sizes.
    const int n = tp_dbl.size();
    output = Rcpp::NumericVector(n);

    // 1) Get raw pointers to the data for faster access
    const double* tp_ptr = tp_dbl.data();
    const double* fp_ptr = fp_dbl.data();
    double* output_ptr = REAL(output);

    // 2) Use a pointer-based loop to calculate recall (TPR) element-wise
    for (int i = 0; i < n; ++i) {
      output_ptr[i] = tp_ptr[i] / (tp_ptr[i] + fp_ptr[i]);
    }

    // Set names attribute using reference
    output.attr("names") = actual.attr("levels");

  }

  return output;
}
