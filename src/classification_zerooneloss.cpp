#include <Rcpp.h>
using namespace Rcpp;

//' Zero-One Loss
//'
//' @description
//' The [zerooneloss()]-function computes the [Zero-One Loss](https://en.wikipedia.org/wiki/Loss_functions_for_classification), a classification loss function that calculates the proportion of misclassified instances between
//' two vectors of predicted and observed [factor()] values.
//'
//' @usage
//' zerooneloss(
//'   actual,
//'   predicted
//' )
//'
//' @inherit specificity
//'
//' @section Calculation:
//'
//' Zero-One Loss is a global metric that measures the proportion of incorrect predictions made by the model. It is calculated as follows,
//'
//' \deqn{
//'   \frac{\#FP + \#FN}{\#TP + \#TN + \#FP + \#FN}
//' }
//'
//' Where \eqn{\#TP}, \eqn{\#TN}, \eqn{\#FP}, and \eqn{\#FN} represent the true positives, true negatives, false positives, and false negatives, respectively.
//'
//' Zero-One Loss provides an overall measure of the model's prediction errors across all classes.
//'
//' @returns
//'
//' A <[numeric]>-vector of [length] 1
//'
//' @example man/examples/scr_zerooneloss.R
//'
//' @family classification
//'
//' @export
// [[Rcpp::export]]
double zerooneloss(
    const NumericVector& actual,
    const NumericVector& predicted) {

  const int n = actual.size();

  const double* actual_ptr = actual.begin();
  const double* predicted_ptr = predicted.begin();

  int incorrect_count = 0;

  for (int i = 0; i < n; ++i) {

    incorrect_count += (*(actual_ptr++) != *(predicted_ptr++));

  }

  return static_cast<double> (incorrect_count) / n;
}
