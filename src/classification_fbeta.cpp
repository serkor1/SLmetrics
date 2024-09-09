#include <Rcpp.h>
#include "declarations.h"
using namespace Rcpp;
//' Generalized F Score
//'
//' @description
//' Calculate the F Score
//'
//' @usage
//' fbeta(
//'   actual,
//'   predicted,
//'   beta = 1,
//'   aggregate = FALSE
//' )
//'
//' @inheritParams cmatrix
//' @param beta A <[numeric]> vector of length 1. 1 by default, see details.
//' @param aggregate A <[logical]>-value of [length] 1. [FALSE] by default. If [TRUE] it returns the
//' micro average across all k-classes
//'
//' @details
//' The general F-score equation is given as follows,
//'
//' \deqn{F_{\beta} = (1+\beta^2) \frac{precision \times recall}{\beta^2 \times precision + recall}}
//'
//' if \eqn{\beta = 1} then it corresponds to the traditional F1 score.
//'
//' @returns
//' A named <[numeric]> vector of length k
//'
//' @family classification
//'
// [[Rcpp::export]]
NumericVector fbeta(
    const IntegerVector& actual,
    const IntegerVector& predicted,
    const double& beta = 1.0,
    const bool& aggregate = false) {

  /*
   * This function calculates the F1-score
   * of the classification problem.
   *
   * It needs the precision and
   * recall
   */
  const double beta_sq = beta * beta;
  const NumericVector recall_obj = recall(actual, predicted, aggregate);
  const NumericVector precision_obj = precision(actual, predicted, aggregate);

  NumericVector output = (1 + beta_sq) * (recall_obj * precision_obj) / ( (beta_sq * precision_obj) + recall_obj);

  if (!aggregate) {
    output.attr("names") = actual.attr("levels");
  }

  return output;

}
