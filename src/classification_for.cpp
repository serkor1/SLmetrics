// [[Rcpp::depends(RcppEigen)]]
#include <RcppEigen.h>
#include "helpers.h"
using namespace Rcpp;

//' False Exclusion Rate (FER)
//'
//' The [fer()]-function calculates the False Omission Rate (FOR)
//'
//'
//' @usage
//' # false omission rate
//' fer(
//'   actual,
//'   predicted,
//'   aggregate = FALSE
//' )
//'
//' @inherit specificity
//'
//' @details
//'
//' The False Omission Rate (FOR) is calculated for each class \eqn{k} as follows,
//'
//' \deqn{
//'   \frac{\#FN_k}{\#FN_k + \#TN_k}
//' }
//'
//' Where \eqn{\#FN_k} and \eqn{\#TN_k} are the number of false negatives and true negatives, respectively, for each class \eqn{k}.
//'
//' When `aggregate = TRUE`, the `micro`-average is calculated,
//'
//' \deqn{
//'   \frac{\sum_{k=1}^k \#FN_k}{\sum_{k=1}^k \#FN_k + \sum_{k=1}^k \#TN_k}
//' }
//'
//' @family classification
//' @export
// [[Rcpp::export]]
NumericVector fer(
  const IntegerVector& actual,
  const IntegerVector& predicted,
  const bool& aggregate = false) {

/*
 * Calculate:
 *
 * 1) Confusion Matrix
 * 2) False Negatives
 * 3) True Negatives
 *
 * Output is FOR
 */

const Eigen::MatrixXi& c_matrix        = confmat(actual, predicted);
const Eigen::VectorXi& false_negative  = FN(c_matrix);
const Eigen::VectorXi& true_negative   = TN(c_matrix);

const Eigen::ArrayXd& fn_dbl = false_negative.cast<double>().array();
const Eigen::ArrayXd& tn_dbl = true_negative.cast<double>().array();

Rcpp::NumericVector output;

if (aggregate) {

  const double fn = fn_dbl.sum();
  const double tn = tn_dbl.sum();

  output = Rcpp::NumericVector::create(fn / (tn + fn));

} else {

  const int n = fn_dbl.size();
  output = Rcpp::NumericVector(n);

  const double* fn_ptr = fn_dbl.data();
  const double* tn_ptr = tn_dbl.data();
  double* output_ptr = REAL(output);

  for (int i = 0; i < n; ++i) {
    output_ptr[i] = fn_ptr[i] / (tn_ptr[i] + fn_ptr[i]);
  }

  output.attr("names") = actual.attr("levels");

}

return output;
}
