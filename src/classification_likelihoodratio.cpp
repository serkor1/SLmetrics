// [[Rcpp::depends(RcppEigen)]]
#include <RcppEigen.h>
#include "helpers.h"
using namespace Rcpp;

//' Positive Likelihood (LR+)
//' @usage
//' plr(
//'   actual,
//'   predicted,
//'   aggregate = FALSE
//' )
//'
//' @inherit specificity
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

//' Negative Likelihood Ratio (LR-)
//'
//'
//' @usage
//' nlr(
//'   actual,
//'   predicted,
//'   aggregate = FALSE
//' )
//'
//' @inherit specificity
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

