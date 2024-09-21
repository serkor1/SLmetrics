// [[Rcpp::depends(RcppEigen)]]
#include <RcppEigen.h>
#include "helpers.h"
using namespace Rcpp;

//' Positive Likelihood Ratio (PLR)
//'
//' @description
//' The [plr()]-function computes the [positive likelihood ratio](https://en.wikipedia.org/wiki/Likelihood_ratios_in_diagnostic_testing), also known as the likelihood ratio for positive results, between
//' two vectors of predicted and observed [factor()] values. When `aggregate = TRUE`, the function returns the micro-average PLR across all classes \eqn{k}.
//' By default, it returns the class-wise PLR.
//'
//' @usage
//' plr(
//'   actual,
//'   predicted,
//'   aggregate = FALSE
//' )
//'
//' @example man/examples/scr_plr_nlr.R
//'
//' @inherit specificity
//'
//' @section Calculation:
//'
//' The Positive Likelihood Ratio (PLR) is calculated for each class \eqn{k} as follows,
//'
//' \deqn{
//'   \frac{\text{Sensitivity}_k}{1 - \text{Specificity}_k}
//' }
//'
//' Where sensitivity (or true positive rate) is calculated as \eqn{\frac{\#TP_k}{\#TP_k + \#FN_k}} and specificity (or true negative rate) is calculated as \eqn{\frac{\#TN_k}{\#TN_k + \#FP_k}}.
//'
//' When `aggregate = TRUE`, the `micro`-average is calculated,
//'
//' \deqn{
//'   \frac{\sum_{k=1}^k \text{Sensitivity}_k}{1 - \sum_{k=1}^k \text{Specificity}_k}
//' }
//'
//' @seealso
//'
//' The [nlr()]-function for the Negative Likehood Ratio (LR-)
//'
//' @family classification
//' @export
// [[Rcpp::export]]
NumericVector plr(
   const IntegerVector& actual,
   const IntegerVector& predicted,
   const bool& aggregate = false) {

 /*
  * Calculate:
  *
  * 1) Sensitivity (TPR)
  * 2) Specificity (TNR)
  *
  * Output is PLR
  */

 const Eigen::MatrixXi& c_matrix        = confmat(actual, predicted);
 const Eigen::VectorXi& true_positive   = TP(c_matrix);
 const Eigen::VectorXi& false_negative  = FN(c_matrix);
 const Eigen::VectorXi& true_negative   = TN(c_matrix);
 const Eigen::VectorXi& false_positive  = FP(c_matrix);

 const Eigen::ArrayXd& tp_dbl = true_positive.cast<double>().array();
 const Eigen::ArrayXd& fn_dbl = false_negative.cast<double>().array();
 const Eigen::ArrayXd& tn_dbl = true_negative.cast<double>().array();
 const Eigen::ArrayXd& fp_dbl = false_positive.cast<double>().array();

 Rcpp::NumericVector output;

 if (aggregate) {

   const double sensitivity = tp_dbl.sum() / (tp_dbl.sum() + fn_dbl.sum());
   const double specificity = tn_dbl.sum() / (tn_dbl.sum() + fp_dbl.sum());

   output = Rcpp::NumericVector::create(sensitivity / (1.0 - specificity));

 } else {

   const int n = tp_dbl.size();
   output = Rcpp::NumericVector(n);

   const double* tp_ptr = tp_dbl.data();
   const double* fn_ptr = fn_dbl.data();
   const double* tn_ptr = tn_dbl.data();
   const double* fp_ptr = fp_dbl.data();
   double* output_ptr = REAL(output);

   for (int i = 0; i < n; ++i) {
     const double sensitivity = tp_ptr[i] / (tp_ptr[i] + fn_ptr[i]);
     const double specificity = tn_ptr[i] / (tn_ptr[i] + fp_ptr[i]);
     output_ptr[i] = sensitivity / (1.0 - specificity);
   }

   output.attr("names") = actual.attr("levels");

 }

 return output;
}

//' Negative Likelihood Ratio (NLR)
//'
//' @description
//' The [nlr()]-function computes the [negative likelihood ratio](https://en.wikipedia.org/wiki/Likelihood_ratios_in_diagnostic_testing), also known as the likelihood ratio for negative results, between
//' two vectors of predicted and observed [factor()] values. When `aggregate = TRUE`, the function returns the micro-average NLR across all classes \eqn{k}.
//' By default, it returns the class-wise NLR.
//'
//' @usage
//' nlr(
//'   actual,
//'   predicted,
//'   aggregate = FALSE
//' )
//'
//' @example man/examples/scr_plr_nlr.R
//'
//' @inherit specificity
//'
//' @section Calculation:
//'
//' The Negative Likelihood Ratio (NLR) is calculated for each class \eqn{k} as follows,
//'
//' \deqn{
//'   \frac{1 - \text{Sensitivity}_k}{\text{Specificity}_k}
//' }
//'
//' Where sensitivity (or true positive rate) is calculated as \eqn{\frac{\#TP_k}{\#TP_k + \#FN_k}} and specificity (or true negative rate) is calculated as \eqn{\frac{\#TN_k}{\#TN_k + \#FP_k}}.
//'
//' When `aggregate = TRUE`, the `micro`-average is calculated,
//'
//' \deqn{
//'   \frac{\sum_{k=1}^k (1 - \text{Sensitivity}_k)}{\sum_{k=1}^k \text{Specificity}_k}
//' }
//'
//' @seealso
//'
//' The [plr()]-function for the Positive Likehood Ratio (LR+)
//' @family classification
//' @export
// [[Rcpp::export]]
NumericVector nlr(
    const IntegerVector& actual,
    const IntegerVector& predicted,
    const bool& aggregate = false) {

  /*
   * Calculate:
   *
   * 1) Sensitivity (TPR)
   * 2) Specificity (TNR)
   *
   * Output is NLR
   */

  const Eigen::MatrixXi& c_matrix        = confmat(actual, predicted);
  const Eigen::VectorXi& true_positive   = TP(c_matrix);
  const Eigen::VectorXi& false_negative  = FN(c_matrix);
  const Eigen::VectorXi& true_negative   = TN(c_matrix);
  const Eigen::VectorXi& false_positive  = FP(c_matrix);

  const Eigen::ArrayXd& tp_dbl = true_positive.cast<double>().array();
  const Eigen::ArrayXd& fn_dbl = false_negative.cast<double>().array();
  const Eigen::ArrayXd& tn_dbl = true_negative.cast<double>().array();
  const Eigen::ArrayXd& fp_dbl = false_positive.cast<double>().array();

  Rcpp::NumericVector output;

  if (aggregate) {

    const double sensitivity = tp_dbl.sum() / (tp_dbl.sum() + fn_dbl.sum());
    const double specificity = tn_dbl.sum() / (tn_dbl.sum() + fp_dbl.sum());

    output = Rcpp::NumericVector::create((1.0 - sensitivity) / specificity);

  } else {

    const int n = tp_dbl.size();
    output = Rcpp::NumericVector(n);

    const double* tp_ptr = tp_dbl.data();
    const double* fn_ptr = fn_dbl.data();
    const double* tn_ptr = tn_dbl.data();
    const double* fp_ptr = fp_dbl.data();
    double* output_ptr = REAL(output);

    for (int i = 0; i < n; ++i) {
      const double sensitivity = tp_ptr[i] / (tp_ptr[i] + fn_ptr[i]);
      const double specificity = tn_ptr[i] / (tn_ptr[i] + fp_ptr[i]);
      output_ptr[i] = (1.0 - sensitivity) / specificity;
    }

    output.attr("names") = actual.attr("levels");

  }

  return output;
}

