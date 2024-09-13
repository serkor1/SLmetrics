// [[Rcpp::depends(RcppEigen)]]
#include <RcppEigen.h>
#include "helpers.h"
using namespace Rcpp;

//' Specificity (True Negative Rate)
//'
//' @description
//' Calculate the specificity
//'
//' @usage
//' specificity(
//'   actual,
//'   predicted,
//'   aggregate = FALSE
//' )
//'
//' @inheritParams cmatrix
//' @param aggregate A <[logical]>-value of [length] 1. [FALSE] by default. If [TRUE] it returns the
//' micro average across all k-classes
//'
//' @returns A named <[numeric]>-vector of length k.
//'
//' @example man/examples/scr_specificity.R
//'
//'
//' @family classification
//'
//' @export
// [[Rcpp::export]]
inline NumericVector specificity(
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

   output = Rcpp::NumericVector::create(tn / (tn + fp));

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
     output_ptr[i] = fp_ptr[i] / (fp_ptr[i] + tn_ptr[i]);
   }

   // Set names attribute using reference
   output.attr("names") = actual.attr("levels");

 }

 return output;

}

//' @rdname specificity
//'
//' @usage
//' tnr(
//'   actual,
//'   predicted,
//'   aggregate = FALSE
//' )
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
