#include <Rcpp.h>
using namespace Rcpp;

//' Accuracy
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
