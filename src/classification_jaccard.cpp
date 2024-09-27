// [[Rcpp::depends(RcppEigen)]]
#include <RcppEigen.h>
#include "helpers.h"
#include <cmath>
using namespace Rcpp;

//' Compute the \eqn{\text{Jaccard}} \eqn{\text{index}}
//'
//' @description
//' The [jaccard()]-function computes the [Jaccard Index](https://en.wikipedia.org/wiki/Jaccard_index), also known as the Intersection over Union, between
//' two vectors of predicted and observed [factor()] values.
//'
//' When `aggregate = TRUE`, the function returns the micro-average Jaccard Index across all classes \eqn{k}.
//' By default, it returns the class-wise Jaccard Index.
//'
//' @usage
//' # using `jaccard()`-function
//' jaccard(
//'   actual,
//'   predicted,
//'   aggregate = FALSE
//' )
//'
//' @inherit specificity
//'
//' @section Calculation:
//'
//' The metric is calcualted for each class \eqn{k} as follows,
//'
//' \deqn{
//'   \frac{\#TP_k}{\#TP_k + \#FP_k + \#FN_k}
//' }
//'
//' Where \eqn{\#TP_k}, \eqn{\#FP_k}, and \eqn{\#FN_k} represent the number of true positives, false positives, and false negatives for each class \eqn{k}, respectively.
//'
//' When `aggregate = TRUE`, the micro-average is calculated as,
//'
//' \deqn{
//'   \frac{\sum_{i = 1}^{k} TP_i}{\sum_{i = 1}^{k} TP_i + \sum_{i = 1}^{k} FP_k + \sum_{i = 1}^{k} FN_k}
//' }
//'
//' @example man/examples/scr_jaccard.R
//'
//' @family classification
//'
//' @export
// [[Rcpp::export]]
Rcpp::NumericVector jaccard(
      const IntegerVector& actual,
      const IntegerVector& predicted,
      const bool& aggregate = false) {

   // 0) calculate the confusion matrix, TP, FP, and FN
   const Eigen::MatrixXi& c_matrix        = confmat(actual, predicted);
   const Eigen::VectorXi& true_positive   = TP(c_matrix);
   const Eigen::VectorXi& false_positive  = FP(c_matrix);
   const Eigen::VectorXi& false_negative  = FN(c_matrix);

   // 1) cast the integer vectors to double arrays
   const Eigen::ArrayXd& tp_dbl = true_positive.cast<double>().array();
   const Eigen::ArrayXd& fp_dbl = false_positive.cast<double>().array();
   const Eigen::ArrayXd& fn_dbl = false_negative.cast<double>().array();

   // 2) declare output vector
   Rcpp::NumericVector output;

   if (aggregate) {

      const double tp = tp_dbl.sum();
      const double fp = fp_dbl.sum();
      const double fn = fn_dbl.sum();

      // Handle division by zero case
      output = Rcpp::NumericVector::create((tp + fp + fn == 0) ? 0.0 : (tp / (tp + fp + fn)));

   } else {

      const int n = tp_dbl.size();
      output = Rcpp::NumericVector(n);

      const double* tp_ptr = tp_dbl.data();
      const double* fp_ptr = fp_dbl.data();
      const double* fn_ptr = fn_dbl.data();
      double* output_ptr = REAL(output);

      for (int i = 0; i < n; ++i) {
         const double denom = tp_ptr[i] + fp_ptr[i] + fn_ptr[i];
         output_ptr[i] = (denom == 0) ? NA_REAL : (tp_ptr[i] / denom);

      }

      // Set names attribute using reference
      output.attr("names") = actual.attr("levels");

   }

   return output;
}

//' @rdname jaccard
//'
//' @usage
//' # using `csi()`-function
//' csi(
//'   actual,
//'   predicted,
//'   aggregate = FALSE
//' )
//' @export
// [[Rcpp::export]]
Rcpp::NumericVector csi(
      const IntegerVector& actual,
      const IntegerVector& predicted,
      const bool& aggregate = false) {

   return jaccard(actual, predicted, aggregate);

}

//' @rdname jaccard
//'
//' @usage
//' # using `tscore()`-function
//' tscore(
//'   actual,
//'   predicted,
//'   aggregate = FALSE
//' )
//' @export
// [[Rcpp::export]]
 Rcpp::NumericVector tscore(
       const IntegerVector& actual,
       const IntegerVector& predicted,
       const bool& aggregate = false) {

    return jaccard(actual, predicted, aggregate);

 }
