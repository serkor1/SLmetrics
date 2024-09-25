// [[Rcpp::depends(RcppEigen)]]
#include <RcppEigen.h>
#include "helpers.h"
using namespace Rcpp;

//' Compute the \eqn{\text{accuracy}}
//'
//' The [accuracy()]-function computes the [accuracy](https://en.wikipedia.org/wiki/Precision_and_recall) between two
//' vectors of predicted and observed [factor()] values.
//'
//' @usage
//' accuracy(
//'   actual,
//'   predicted
//' )
//'
//' @inherit specificity
//'
//' @section Calculation:
//'
//' Accuracy is a global metric that measures the proportion of correct predictions (both true positives and true negatives) out of all predictions, and is calculated as follows,
//'
//' \deqn{
//'   \frac{\#TP + \#TN}{\#TP + \#TN + \#FP + \#FN}
//' }
//'
//' Where \eqn{\#TP}, \eqn{\#TN}, \eqn{\#FP}, and \eqn{\#FN} represent the true positives, true negatives, false positives, and false negatives, respectively.
//'
//' Accuracy provides an overall performance measure of the model across all classes.
//'
//' @returns
//'
//' A <[numeric]>-vector of [length] 1
//'
//' @example man/examples/scr_accuracy.R
//'
//' @family classification
//'
//' @export
// [[Rcpp::export]]
double accuracy(
    const NumericVector& actual,
    const NumericVector& predicted) {

  const int n = actual.size();

  const double* actual_ptr = actual.begin();
  const double* predicted_ptr = predicted.begin();

  int correct_count = 0;

  for (int i = 0; i < n; ++i) {

    correct_count += (*(actual_ptr++) == *(predicted_ptr++));

  }

  return static_cast<double> (correct_count) / n;
}

//' Compute the \eqn{\text{balanced accuracy}}
//'
//' The [baccuracy()]-function computes the [balanced accuracy](https://neptune.ai/blog/balanced-accuracy) between two
//' vectors of predicted and observed [factor()] values.
//'
//' @usage
//' baccuracy(
//'   actual,
//'   predicted,
//'   adjust = FALSE
//' )
//'
//' @inherit specificity
//' @param adjust A [logical] value. [FALSE] by default. If [TRUE] the metric is adjusted for random change \eqn{\frac{1}{k}}
//'
//' @section Calculation:
//'
//' The metric is calculated as follows,
//'
//' \deqn{
//'   \frac{\text{sensitivity} + \text{specificty}}{2}
//' }
//'
//' See the [sensitivity()]- and/or [specificity()]-function for more details.
//'
//' @returns
//'
//' A [numeric]-vector of [length] 1
//'
//' @example man/examples/scr_baccuracy.R
//'
//' @family classification
//'
//' @export
// [[Rcpp::export]]
double baccuracy(
    const Rcpp::IntegerVector& actual,
    const Rcpp::IntegerVector& predicted,
    const bool adjust = false) {

  /*
   * Calculate the balanced accuracy
   * NOTE: This could be incorporated
   * in the accuracy function
   */

  // 0) Generate the
  // confusion matrix and
  // count the number of classes k
  Eigen::MatrixXi c_matrix = confmat(actual, predicted);
  int k = Rcpp::as<Rcpp::CharacterVector>(actual.attr("levels")).size();

  // 1) calculate the row sums
  // and extract the diagonal of the
  // matrix
  Eigen::VectorXi row_sums = c_matrix.rowwise().sum();
  Eigen::VectorXi diag = c_matrix.diagonal();

  // 2) class-wise sum
  // and valid_classes
  double per_class_sum = 0.0;
  int valid_classes = 0;

  // 3) loop through
  // valid cases and increment
  // accordingly
  for (int i = 0; i < k; ++i) {

    if (row_sums(i) > 0) {

      per_class_sum += static_cast<double>(diag(i)) / row_sums(i);
      ++valid_classes;

    }

  }

  // 4) calculate balanced accuracy
  // accordingly
  double output = per_class_sum / valid_classes;

  // 5) adjust for chance
  // findings
  if (adjust && valid_classes > 0) {

    double chance = 1.0 / valid_classes;
    output = (output - chance) / (1.0 - chance);

  }

  return output;

}





