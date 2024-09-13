// [[Rcpp::depends(RcppEigen)]]
#include <RcppEigen.h>
#include "helpers.h"
using namespace Rcpp;

//' Negative Predictive Value (NPV)
//'
//' @description
//' Calculate the sensitivity
//'
//' @usage
//' npv(
//'   actual,
//'   predicted,
//'   aggregate = FALSE
//' )
//'
//' @inheritParams recall
//'
//' @family classification
//'
//' @export
// [[Rcpp::export]]
NumericVector npv(
   const IntegerVector& actual,
   const IntegerVector& predicted,
   const bool& aggregate = false) {

 /*
  * Calculate:
  *
  * 1) Confusion Matrix
  * 2) True Positives
  * 3) False Positive
  *
  * Output is precision
  */

 // 0) calculate the
 // confusion matrix, TP and FP
 const Eigen::MatrixXi& c_matrix        = confmat(actual, predicted);
 const Eigen::VectorXi& true_negative   = TN(c_matrix);
 const Eigen::VectorXi& false_negative  = FN(c_matrix);

 // 1) caste the integer vectors
 // to double arrays
 const Eigen::ArrayXd& tn_dbl = true_negative.cast<double>().array();
 const Eigen::ArrayXd& fn_dbl = false_negative.cast<double>().array();

 // 2) declare output
 // vector
 Rcpp::NumericVector output;

 if (aggregate) {

   const double tn = tn_dbl.sum();
   const double pn = fn_dbl.sum() + tn_dbl.sum();

   output = Rcpp::NumericVector::create(tn / pn);

 } else {

   // 0) calculate length
   // of the vector to avoid
   // dynamic allocation of vector
   // sizes.
   const int n = tn_dbl.size();
   output = Rcpp::NumericVector(n);

   // 1) Get raw pointers to the data for faster access
   const double* tn_ptr = tn_dbl.data();
   const double* fn_ptr = fn_dbl.data();
   double* output_ptr = REAL(output);

   // 2) Use a pointer-based loop to calculate recall (TPR) element-wise
   for (int i = 0; i < n; ++i) {
     output_ptr[i] = tn_ptr[i] / (tn_ptr[i] + fn_ptr[i]);
   }

   // Set names attribute using reference
   output.attr("names") = actual.attr("levels");

 }

 return output;
}
