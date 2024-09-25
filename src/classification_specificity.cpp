// [[Rcpp::depends(RcppEigen)]]
#include <RcppEigen.h>
#include "helpers.h"
using namespace Rcpp;

//' Specificity (True Negative Rate)
//'
//' @description
//' The  [specificity()]-function computes the [specificity](https://en.wikipedia.org/wiki/Sensitivity_and_specificity), also known as the True Negative Rate (TNR) or selectivity, between
//' two vectors of predicted and observed [factor()] values. When `aggregate = TRUE`, the function returns the micro-average specificity across all classes \eqn{k}.
//' By default, it returns the class-wise specificity.
//'
//'
//' @usage
//' # using `specificity()`
//' specificity(
//'   actual,
//'   predicted,
//'   aggregate = FALSE
//' )
//'
//' @inheritParams cmatrix
//' @param aggregate A <[logical]>-value of [length] \eqn{1}. [FALSE] by default. If [TRUE] it returns the
//' micro average across all \eqn{k} classes
//'
//' @details
//'
//' Consider a classification problem with three classes: `A`, `B`, and `C`. The actual vector of [factor()] values is defined as follows:
//'
//' ```{r output, echo = TRUE}
//' ## set seed
//' set.seed(1903)
//'
//' ## actual
//' factor(
//'   x = sample(x = 1:3, size = 10, replace = TRUE),
//'   levels = c(1, 2, 3),
//'   labels = c("A", "B", "C")
//' )
//' ```
//'
//' Here, the values 1, 2, and 3 are mapped to `A`, `B`, and `C`, respectively. Now, suppose your model does not predict any `B`'s. The predicted vector of [factor()] values would be defined as follows:
//'
//' ```{r output, echo = TRUE}
//' ## set seed
//' set.seed(1903)
//'
//' ## predicted
//' factor(
//'   x = sample(x = c(1, 3), size = 10, replace = TRUE),
//'   levels = c(1, 2, 3),
//'   labels = c("A", "B", "C")
//' )
//' ```
//'
//' In both cases, \eqn{k = 3}, determined indirectly by the `levels` argument.
//'
//' @returns
//'
//' If `aggregate` is [FALSE] (the default), a named <[numeric]>-vector of [length] k
//'
//' If `aggregate` is [TRUE], a <[numeric]>-vector of [length] 1
//'
//' @example man/examples/scr_specificity.R
//'
//'
//' @section Calculation:
//' The metric is calculated for each class \eqn{k} as follows,
//'
//' \deqn{
//'   \frac{\#TN_k}{\#TN_k+\#FP_k}
//' }
//'
//' Where \eqn{\#TN_k} and \eqn{\#FP_k} is the number of true negatives and false positives, respectively, for each class \eqn{k}.
//'
//' When `aggregate = TRUE` the `micro`-average is calculated,
//'
//' \deqn{
//'   \frac{\sum_{k=1}^k \#TN_k}{\sum_{k=1}^k \#TN_k + \sum_{k=1}^k \#FP_k}
//' }
//'
//'
//' @family classification
//'
//' @export
// [[Rcpp::export]]
NumericVector specificity(
      const IntegerVector& actual,
      const IntegerVector& predicted,
      const bool& aggregate = false) {


   /*
    * Calculate:
    *
    * 1) Confusion Matrix
    * 2) TP, FP, TN, FN
    *
    * Output is specificity
    */

   // 0) calculate the
   // confusion matrix, TP, FP and TN
   const Eigen::MatrixXi& c_matrix        = confmat(actual, predicted);
   const Eigen::VectorXi& false_positive  = FP(c_matrix);
   const Eigen::VectorXi& true_negative   = TN(c_matrix);

   // 1) Cast the integer vectors
   // to double arrays
   const Eigen::ArrayXd& fp_dbl = false_positive.cast<double>().array();
   const Eigen::ArrayXd& tn_dbl = true_negative.cast<double>().array();

   // 2) declare the output
   // vector
   Rcpp::NumericVector output;

   if (aggregate) {

      const double fp = fp_dbl.sum();
      const double tn = tn_dbl.sum();

      output = Rcpp::NumericVector::create((fp + tn == 0) ? 0.0 : tn / (tn + fp));

   } else {

      // 0) calculate length
      // of the vector to avoid
      // dynamic allocation of vector
      // sizes.
      const int n = fp_dbl.size();
      output = Rcpp::NumericVector(n);

      // 1) Get raw pointers to the data for faster access
      const double* fp_ptr = fp_dbl.data();
      const double* tn_ptr = tn_dbl.data();
      double* output_ptr = REAL(output);

      // 2) Use a pointer-based loop to calculate recall (TPR) element-wise
      for (int i = 0; i < n; ++i) {

         const double denominator = (fp_ptr[i] + tn_ptr[i]);
         output_ptr[i] = (denominator == 0) ? 0.0 : tn_ptr[i] / denominator;

      }

      // Set names attribute using reference
      output.attr("names") = actual.attr("levels");

   }

   return output;

}

//' @rdname specificity
//'
//' @usage
//' # using `tnr()`
//' tnr(
//'   actual,
//'   predicted,
//'   aggregate = FALSE
//' )
//'
//' @export
// [[Rcpp::export]]
NumericVector tnr(
      const IntegerVector& actual,
      const IntegerVector& predicted,
      const bool& aggregate = false) {

   return specificity(actual, predicted, aggregate);

}

//' @rdname specificity
//'
//' @usage
//' # using `selectivity()`
//' selectivity(
//'   actual,
//'   predicted,
//'   aggregate = FALSE
//' )
//' @export
// [[Rcpp::export]]
NumericVector selectivity(
      const IntegerVector& actual,
      const IntegerVector& predicted,
      const bool& aggregate = false) {

   return specificity(actual, predicted, aggregate);

}
