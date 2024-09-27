// [[Rcpp::depends(RcppEigen)]]
#include <RcppEigen.h>
#include <cmath>
#include "helpers.h"
using namespace Rcpp;


//' Compute the \eqn{\text{Matthews}} \eqn{\text{Correlation}} \eqn{\text{Coefficient}}
//'
//' @description
//' The [mcc()]-function computes the [Matthews Correlation Coefficient](https://en.wikipedia.org/wiki/Matthews_correlation_coefficient) (MCC), also known as the \eqn{\phi}-coefficient, between
//' two vectors of predicted and observed [factor()] values.
//'
//' @usage
//' # 1) `mcc()`-function
//' mcc(
//'   actual,
//'   predicted
//' )
//'
//' @example man/examples/scr_mcc.R
//'
//' @inherit precision
//'
//' @section Calculation:
//'
//' The metric is calculated as follows,
//'
//' \deqn{
//'   \frac{\#TP \times \#TN - \#FP \times \#FN}{\sqrt{(\#TP + \#FP)(\#TP + \#FN)(\#TN + \#FP)(\#TN + \#FN)}}
//' }
//'
//'
//' @returns
//' A named <[numeric]> vector of length k
//'
//' @family classification
//'
//' @export
// [[Rcpp::export]]
double mcc(
      const Rcpp::IntegerVector& actual,
      const Rcpp::IntegerVector& predicted) {

   // Compute confusion matrix
   const Rcpp::NumericMatrix c_matrix  = wrap(confmat(actual, predicted));


   // Compute true positives (assuming TP(c_matrix) gives a vector)
   double n_correct = Rcpp::sum(Rcpp::diag(c_matrix));

   // Get the size of the confusion matrix (N)
   int N = c_matrix.rows();

   NumericVector t_sum(N), p_sum(N);

   for (int i = 0; i < N; ++i) {
      t_sum[i] = sum(c_matrix(i, _));
      p_sum[i] = sum(c_matrix(_, i));
   }

   double n_samples = sum(p_sum);

   double cov_ytyp = n_correct * n_samples - sum(t_sum * p_sum);
   double cov_ypyp = n_samples * n_samples - sum(p_sum * p_sum);
   double cov_ytyt = n_samples * n_samples - sum(t_sum * t_sum);

   /*
    * Calculate the product
    * of the covariance
    *
    * And check if equal to
    * avoid errors
    */

   double product = cov_ypyp * cov_ytyt;

   if (product == 0) {

      return 0.0;

   }

   return cov_ytyp / std::sqrt(product);
}

//' @rdname mcc
//'
//' @usage
//' # 2) `phi()`-function
//' phi(
//'   actual,
//'   predicted
//' )
//'
//' @export
// [[Rcpp::export]]
double phi(
      const Rcpp::IntegerVector& actual,
      const Rcpp::IntegerVector& predicted) {

   /*
    * The MCC coefficient is also known
    * as the phi coefficient
    */

   return mcc(actual, predicted);

}

