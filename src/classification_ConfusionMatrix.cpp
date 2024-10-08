// [[Rcpp::depends(RcppEigen)]]
#include <RcppEigen.h>
#include "src_Helpers.h"
#include <Rcpp.h>
using namespace Rcpp;
//' Confusion Matrix
//'
//' @description
//'
//' The [cmatrix()]-function uses cross-classifying factors to build
//' a confusion matrix of the counts at each combination of the [factor] levels.
//' Each row of the [matrix] represents the actual [factor] levels, while each
//' column represents the predicted [factor] levels.
//'
//' @usage
//' cmatrix(
//'   actual,
//'   predicted
//' )
//'
//' @param actual A <[factor]>-vector of [length] \eqn{n}, and \eqn{k} levels.
//' @param predicted A <[factor]>-vector of [length] \eqn{n}, and \eqn{k} levels.
//'
//' @example man/examples/scr_confusionmatrix.R
//' @family classification
//'
//' @inherit specificity details
//'
//' @section Dimensions:
//'
//' There is no robust defensive measure against misspecififying
//' the confusion matrix. If the arguments are correctly specified, the resulting
//' confusion matrix is on the form:
//'
//' |            | A (Predicted) | B (Predicted) |
//' | :----------|:-------------:| -------------:|
//' | A (Actual) | Value         | Value         |
//' | B (Actual) | Value         | Value         |
//'
//'
//' @returns
//'
//' A named \eqn{k} x \eqn{k} <[matrix]> of [class] <cmatrix>
//'
//' @export
// [[Rcpp::export]]
Rcpp::NumericMatrix cmatrix(
    const Rcpp::IntegerVector& actual,
    const Rcpp::IntegerVector& predicted) {

  /*
   * This function generates a confusion matrix
   * by incrementing locations based on the actual
   * vector. If it includes NA values it will
   * crash, so this function should check for missing
   * values in both vectors. This is for later
   */

  // 1) get levels of the for the
  // naming of the matrix
  const Rcpp::CharacterVector& levels = actual.attr("levels");

  Rcpp::NumericMatrix output = Rcpp::wrap(confmat(actual, predicted));

  // 4) set the dimnames of
  // the confusion matrix
  output.attr("dimnames") = Rcpp::List::create(levels, levels);
  output.attr("class")    = "cmatrix";

  return output;
}
