// [[Rcpp::depends(RcppEigen)]]
#include <RcppEigen.h>
#include "helpers.h"
using namespace Rcpp;

//'  False Positive Rate (fpr)
//' @usage
//' # 3) `fpr()`-function
//' fpr(
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

   output = Rcpp::NumericVector::create(fp / (fp + tn));

 } else {

   const int n = fp_dbl.size();
   output = Rcpp::NumericVector(n);

   const double* fp_ptr = fp_dbl.data();
   const double* tn_ptr = tn_dbl.data();
   double* output_ptr = REAL(output);

   for (int i = 0; i < n; ++i) {
     output_ptr[i] = fp_ptr[i] / (fp_ptr[i] + tn_ptr[i]);
   }

   output.attr("names") = actual.attr("levels");

 }

 return output;
}

//' @rdname fpr
//' @export
// [[Rcpp::export]]
NumericVector fallout(
  const IntegerVector& actual,
  const IntegerVector& predicted,
  const bool& aggregate = false) {

return fpr(actual, predicted, aggregate);
}
