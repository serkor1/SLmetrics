// [[Rcpp::depends(RcppEigen)]]
#include <RcppEigen.h>
#include "helpers.h"
using namespace Rcpp;


//' Recall (Sensitivity)
//'
//' @description
//' Calculate the sensitivity
//'
//' @usage
//'  # 1) `recall()`-function
//' recall(
//'   actual,
//'   predicted,
//'   aggregate = FALSE
//' )
//'
//' @inherit specificity
//'
//' @details
//'
//' The Sensitivity (SEN), also known as Recall or True Positive Rate (TPR). The metric is calculated for each class \eqn{k} as follows,
//'
//' \deqn{
//'   \frac{\#TP_k}{\#TP_k + \#FN_k}
//' }
//'
//' Where \eqn{\#TP_k} and \eqn{\#FN_k} is the number of true positives and false negatives, respectively, for each class \eqn{k}.
//'
//' When `aggregate = TRUE` the `micro`-average is calculated,
//'
//' \deqn{
//'   \frac{\sum_{k=1}^k \#TP_k}{\sum_{k=1}^k \#TP_k + \sum_{k=1}^k \#FN_k}
//' }
//' @family classification
//'
//' @export
// [[Rcpp::export]]
NumericVector recall(
    const IntegerVector& actual,
    const IntegerVector& predicted,
    const bool& aggregate = false) {

  /*
   * Calculate:
   *
   * 1) Confusion Matrix
   * 2) True Positives
   * 3) False Negatives
   *
   * Output is recall
   *
   * NOTE: If aggregate is TRUE then the
   * micro-average is returned.
   */

  // 0) Calculate the
  // confusion matrix, TP and FN
  const Eigen::MatrixXi& c_matrix = confmat(actual, predicted);
  const Eigen::VectorXi& true_positive = TP(c_matrix);
  const Eigen::VectorXi& false_negative = FN(c_matrix);

  // 1) Cast the integer vectors
  // to double Arrays
  const Eigen::ArrayXd& tp_dbl = true_positive.cast<double>().array();
  const Eigen::ArrayXd& fn_dbl = false_negative.cast<double>().array();

  // 2) declare the output
  // vector
  Rcpp::NumericVector output;

  if (aggregate) {
    const double tp = tp_dbl.sum();
    const double fn = fn_dbl.sum();

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
    const double* fn_ptr = fn_dbl.data();
    double* output_ptr = REAL(output);

    // 2) Use a pointer-based loop to calculate recall (TPR) element-wise
    for (int i = 0; i < n; ++i) {
      output_ptr[i] = tp_ptr[i] / (tp_ptr[i] + fn_ptr[i]);
    }

    // Set names attribute using reference
    output.attr("names") = actual.attr("levels");
  }

  return output;
}

//' @rdname recall
//'
//' @usage
//' tpr(
//'   actual,
//'   predicted,
//'   aggregate
//' )
//'
//' @export
// [[Rcpp::export]]
Rcpp::NumericVector tpr(
    const IntegerVector& actual,
    const IntegerVector& predicted,
    const bool& aggregate = false) {


  return recall(actual, predicted, aggregate);

}
