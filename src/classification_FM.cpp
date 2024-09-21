// [[Rcpp::depends(RcppEigen)]]
#include <RcppEigen.h>
#include <Rcpp.h>
#include "helpers.h"
#include <unordered_map>
#include <cmath>
using namespace Rcpp;

//' Fowlkes-Mallows Index (FMI)
//'
//' @description
//' The [fmi()]-function computes the [Fowlkes-Mallows Index](https://en.wikipedia.org/wiki/Fowlkes%E2%80%93Mallows_index) (FMI), a measure of the similarity between two sets of clusterings, between
//' two vectors of predicted and observed [factor()] values.
//'
//' @usage
//' # fowlkes-mallows index
//' fmi(
//'   actual,
//'   predicted
//' )
//'
//' @example man/examples/scr_fmi.R
//'
//' @inherit specificity
//'
//' @section Calculation:
//'
//' The FMI Index is calculated for each class \eqn{k} as follows,
//'
//' \deqn{
//'   \sqrt{\frac{\#TP_k}{\#TP_k + \#FP_k} \times \frac{\#TP_k}{\#TP_k + \#FN_k}}
//' }
//'
//' Where \eqn{\#TP_k}, \eqn{\#FP_k}, and \eqn{\#FN_k} represent the number of true positives, false positives, and false negatives for each class \eqn{k}, respectively.
//'
//'
//' @returns
//' A <[numeric]> vector of [length] 1
//'
//' @family classification
//'
//' @export
// [[Rcpp::export]]
double fmi(
    const Rcpp::IntegerVector& actual,
    const Rcpp::IntegerVector& predicted) {

 /*
  * Calculate the Fowlkes Mallows Index
  *
  * NOTE: The original function is commented
  * down below. This will be tested with RcppEigen
  * has been properly implemented in the package.
  *
  * Doubles are used avoid overflows
  * and returned NaNs
  */

 int n_samples = actual.size();


 const Eigen::MatrixXi& c_matrix = confmat(actual, predicted);
 const int k = c_matrix.rows();

 double tk = 0.0;
 double pk = 0.0;
 double qk = 0.0;


 Eigen::VectorXd row_sums = Eigen::VectorXd::Zero(k);
 Eigen::VectorXd col_sums = Eigen::VectorXd::Zero(k);

 for (int i = 0; i < k; ++i) {
    for (int j = 0; j < k; ++j) {
       double value = static_cast<double>(c_matrix(i, j));
       tk += value * value;
       row_sums(i) += value;
       col_sums(j) += value;
    }
 }

 pk = col_sums.squaredNorm();
 qk = row_sums.squaredNorm();


 tk -= static_cast<double>(n_samples);
 pk -= static_cast<double>(n_samples);
 qk -= static_cast<double>(n_samples);


 if (tk <= 0 || pk <= 0 || qk <= 0) {
    return 0.0;
 }


 return (std::sqrt(tk / pk) * std::sqrt(tk / qk));
}


// double fmi_(
//       const Rcpp::IntegerVector& actual,
//       const Rcpp::IntegerVector& predicted) {
//
//
//    // 0) Calculate the confusion matrix
//    const Eigen::MatrixXi& c_matrix = confmat(actual, predicted);
//
//    // 1) Compute tk (sum of squared elements in the confusion matrix)
//    int tk = (c_matrix.array().square()).sum();
//
//    // 2) Compute pk (sum of squared column sums)
//    Eigen::VectorXi col_sums = c_matrix.colwise().sum();
//    int pk = col_sums.squaredNorm();
//
//    // 3) Compute qk (sum of squared row sums)
//    Eigen::VectorXi row_sums = c_matrix.rowwise().sum();
//    int qk = row_sums.squaredNorm();
//
//    // 4) Adjust for the sample size by subtracting n_samples from tk, pk, and qk
//    tk -= n_samples;
//    pk -= n_samples;
//    qk -= n_samples;
//
//    // 5) Return the FMI, ensuring no division by zero
//    return tk == 0 ? 0.0 : (std::sqrt((double)tk / pk) * std::sqrt((double)tk / qk));
// }



