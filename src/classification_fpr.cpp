// [[Rcpp::depends(RcppEigen)]]
#include <RcppEigen.h>
#include "helpers.h"
using namespace Rcpp;

//' False Positive Rate (FPR)
//'
//' @description
//' The [fpr()]-function computes the [False Positive Rate](https://en.wikipedia.org/wiki/False_positive_rate) (FPR), also known as the fall-out ([fallout()]), between
//' two vectors of predicted and observed [factor()] values. When `aggregate = TRUE`, the function returns the micro-average FPR across all classes \eqn{k}.
//' By default, it returns the class-wise FPR.
//'
//' @usage
//' # using`fpr()`
//' fpr(
//'   actual,
//'   predicted,
//'   aggregate = FALSE
//' )
//'
//' @inherit specificity
//'
//' @example man/examples/scr_fpr.R
//'
//' @section Calculation:
//'
//' The False Positive Rate (FPR) for each class \eqn{k} is calculated as follows,
//'
//' \deqn{
//'   \frac{\#FP_k}{\#FP_k + \#TN_k}
//' }
//'
//' Where \eqn{\#FP_k} and \eqn{\#TN_k} represent the number of false positives and true negatives, respectively, for each class \eqn{k}.
//'
//' When `aggregate = TRUE`, the micro-average is calculated across all classes,
//'
//' \deqn{
//'   \frac{\sum_{k=1}^k \#FP_k}{\sum_{k=1}^k \#FP_k + \sum_{k=1}^k \#TN_k}
//' }
//'
//' The FPR is the complement of specificity, such that \eqn{\text{FPR} = 1 - \text{Specificity}}.
//'
//' @family classification
//' @export
// [[Rcpp::export]]
NumericVector fpr(
      const IntegerVector& actual,
      const IntegerVector& predicted,
      const bool& aggregate = false) {

   /*
    * Calculate:
    *
    * 1) Confusion Matrix
    * 2) False Positives
    * 3) True Negatives
    *
    * Output is FPR
    */

   const Eigen::MatrixXi& c_matrix        = confmat(actual, predicted);
   const Eigen::VectorXi& false_positive  = FP(c_matrix);
   const Eigen::VectorXi& true_negative   = TN(c_matrix);

   const Eigen::ArrayXd& fp_dbl = false_positive.cast<double>().array();
   const Eigen::ArrayXd& tn_dbl = true_negative.cast<double>().array();

   Rcpp::NumericVector output;

   if (aggregate) {

      const double fp = fp_dbl.sum();
      const double tn = tn_dbl.sum();

      output = Rcpp::NumericVector::create(
         (fp + tn == 0) ? 0.0 : fp / (fp + tn)
         );

   } else {

      const int n = fp_dbl.size();
      output = Rcpp::NumericVector(n);

      const double* fp_ptr = fp_dbl.data();
      const double* tn_ptr = tn_dbl.data();
      double* output_ptr = REAL(output);

      for (int i = 0; i < n; ++i) {

         const double denominator =  (fp_ptr[i] + tn_ptr[i]);

         output_ptr[i] = (denominator == 0) ? 0.0 : fp_ptr[i] / denominator;

      }

      output.attr("names") = actual.attr("levels");

   }

   return output;

}

//' @rdname fpr
//' @usage
//' # using `fallout()`
//' fallout(
//'   actual,
//'   predicted,
//'   aggregate = FALSE
//' )
//' @export
// [[Rcpp::export]]
NumericVector fallout(
      const IntegerVector& actual,
      const IntegerVector& predicted,
      const bool& aggregate = false) {

   return fpr(actual, predicted, aggregate);
}
