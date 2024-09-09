// [[Rcpp::depends(RcppEigen)]]
#include <RcppEigen.h>
#include "helpers.h"
#include <Rcpp.h>
using namespace Rcpp;
//' Confusion Matrix
//'
//' @description
//' Placeholder
//'
//' @usage
//' cmatrix(
//'   actual,
//'   predicted
//' )
//'
//' @param actual A <[factor]>-vector of length n, and k levels.
//' @param predicted A <[factor]>-vector of length n.
//'
//' @example man/examples/scr_confusionmatrix.R
//' @family classification
//'
//' @details
//'
//' If the function is correctly implemented the resulting
//' confusion matrix is given as,
//'
//'
//' |            | A (Predicted)        | B (Predicted)   |
//' | ------------- |:-------------:| -----:|
//' | A (Actual)   | Value     | Value |
//' | B  (Actual)   |  Value    |  Value   |
//'
//'
//' @returns A named k x k <[matrix]>
//'
//' @export
// [[Rcpp::export]]
NumericMatrix cmatrix(
    const IntegerVector& actual,
    const IntegerVector& predicted) {

  /*
   * This function generates a confusion matrix
   * by incrementing locations based on the actual
   * vector. If it includes NA values it will
   * crash, so this function should check for missing
   * values in both vectors. This is for later
   */

  // 1) get levels of the for the
  // naming of the matrix
  const CharacterVector& levels = actual.attr("levels");

  NumericMatrix output = wrap(confmat(actual, predicted));

  // 4) set the dimnames of
  // the confusion matrix
  output.attr("dimnames") = List::create(levels, levels);

  return output;
}



