// [[Rcpp::depends(RcppEigen)]]
#include <RcppEigen.h>
#include "helpers.h"
using namespace Rcpp;

//' Diagnostic Odds Ratio (DOR)
//' @usage
//' # 3) `dor()`-function
//' dor(
//'   actual,
//'   predicted,
//'   aggregate = FALSE
//' )
//'
//' @inherit specificity
//'
//' @family classification
//' @export
// [[Rcpp::export]]
NumericVector dor(
   const IntegerVector& actual,
   const IntegerVector& predicted,
   const bool& aggregate = false) {

 /*
  * Calculate:
  *
  * 1) True Positives
  * 2) False Positives
  * 3) True Negatives
  * 4) False Negatives
  *
  * Output is DOR
  */

 const Eigen::MatrixXi& c_matrix        = confmat(actual, predicted);
 const Eigen::VectorXi& true_positive   = TP(c_matrix);
 const Eigen::VectorXi& false_positive  = FP(c_matrix);
 const Eigen::VectorXi& true_negative   = TN(c_matrix);
 const Eigen::VectorXi& false_negative  = FN(c_matrix);

 const Eigen::ArrayXd& tp_dbl = true_positive.cast<double>().array();
 const Eigen::ArrayXd& fp_dbl = false_positive.cast<double>().array();
 const Eigen::ArrayXd& tn_dbl = true_negative.cast<double>().array();
 const Eigen::ArrayXd& fn_dbl = false_negative.cast<double>().array();

 Rcpp::NumericVector output;

 if (aggregate) {

   const double tp = tp_dbl.sum();
   const double fp = fp_dbl.sum();
   const double tn = tn_dbl.sum();
   const double fn = fn_dbl.sum();

   output = Rcpp::NumericVector::create((tp * tn) / (fp * fn));

 } else {

   const int n = tp_dbl.size();
   output = Rcpp::NumericVector(n);

   const double* tp_ptr = tp_dbl.data();
   const double* fp_ptr = fp_dbl.data();
   const double* tn_ptr = tn_dbl.data();
   const double* fn_ptr = fn_dbl.data();
   double* output_ptr = REAL(output);

   for (int i = 0; i < n; ++i) {
     output_ptr[i] = (tp_ptr[i] * tn_ptr[i]) / (fp_ptr[i] * fn_ptr[i]);
   }

   output.attr("names") = actual.attr("levels");

 }

 return output;
}
