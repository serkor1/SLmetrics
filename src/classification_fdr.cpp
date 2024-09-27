// [[Rcpp::depends(RcppEigen)]]
#include <RcppEigen.h>
#include "helpers.h"
using namespace Rcpp;

//' Compute the \eqn{\text{false}} \eqn{\text{discovery}} \eqn{\text{rate}}
//'
//' @description
//' The [fdr()]-function computes the [false discovery rate](https://en.wikipedia.org/wiki/False_discovery_rate) (FDR), the proportion of false positives among the predicted positives, between
//' two vectors of predicted and observed [factor()] values.
//'
//' When `aggregate = TRUE`, the function returns the micro-average FDR across all classes \eqn{k}. By default, it returns the class-wise FDR.
//'
//' @example man/examples/scr_fdr.R
//'
//' @usage
//' # false discovery rate;
//' fdr(
//'   actual,
//'   predicted,
//'   aggregate = FALSE
//' )
//'
//'
//' @inherit specificity
//'
//' @section Calculation:
//'
//' The metric is calculated for each class \eqn{k} as follows,
//'
//' \deqn{
//'   \frac{\#FP_k}{\#TP_k+\#FP_k}
//' }
//'
//' Where \eqn{\#TP_k} and \eqn{\#FP_k} is the number of true psotives and false positives, respectively, for each class \eqn{k}.
//'
//' When `aggregate = TRUE` the `micro`-average is calculated,
//'
//' \deqn{
//'  \frac{\sum_{k=1}^k \#FP_k}{\sum_{k=1}^k \#TP_k + \sum_{k=1}^k \#FP_k}
//' }
//'
//' @family classification
//' @export
// [[Rcpp::export]]
NumericVector fdr(
   const IntegerVector& actual,
   const IntegerVector& predicted,
   const bool& aggregate = false) {

 /*
  * Calculate:
  *
  * 1) Confusion Matrix
  * 2) False Positives
  * 3) True Positives
  *
  * Output is FDR
  */

 const Eigen::MatrixXi& c_matrix        = confmat(actual, predicted);
 const Eigen::VectorXi& false_positive  = FP(c_matrix);
 const Eigen::VectorXi& true_positive   = TP(c_matrix);

 const Eigen::ArrayXd& fp_dbl = false_positive.cast<double>().array();
 const Eigen::ArrayXd& tp_dbl = true_positive.cast<double>().array();

 Rcpp::NumericVector output;

 if (aggregate) {

   const double fp = fp_dbl.sum();
   const double tp = tp_dbl.sum();

   output = Rcpp::NumericVector::create(fp / (tp + fp));

 } else {

   const int n = fp_dbl.size();
   output = Rcpp::NumericVector(n);

   const double* fp_ptr = fp_dbl.data();
   const double* tp_ptr = tp_dbl.data();
   double* output_ptr = REAL(output);

   for (int i = 0; i < n; ++i) {
     output_ptr[i] = fp_ptr[i] / (tp_ptr[i] + fp_ptr[i]);
   }

   output.attr("names") = actual.attr("levels");

 }

 return output;
}
