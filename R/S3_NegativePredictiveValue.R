# script: Negative Predictive Value
# date: 2024-10-07
# author: Serkan Korkmaz, serkor1@duck.com
# objective:
# script start;

#' Compute the \eqn{\text{negative}} \eqn{\text{predictive}} \eqn{\text{value}}
#'
#' @description
#' The [npv()]-function computes the [negative predictive value](https://en.wikipedia.org/wiki/Positive_and_negative_predictive_values), also known as the True Negative Predictive Value, between
#' two vectors of predicted and observed [factor()] values.
#'
#' When `aggregate = TRUE`, the function returns the micro-average NPV across all classes \eqn{k}. By default, it returns the class-wise NPV.
#'
#' @inherit specificity
#'
#' @example man/examples/scr_NegativePredictiveValue.R
#'
#' @section Calculation:
#'
#' The metric is calculated for each class \eqn{k} as follows,
#'
#' \deqn{
#'   \frac{\#TN_k}{\#TN_k + \#FN_k}
#' }
#'
#' Where \eqn{\#TN_k} and \eqn{\#FN_k} are the number of true negatives and false negatives, respectively, for each class \eqn{k}.
#'
#' When `aggregate = TRUE`, the `micro`-average is calculated,
#'
#' \deqn{
#'   \frac{\sum_{k=1}^k \#TN_k}{\sum_{k=1}^k \#TN_k + \sum_{k=1}^k \#FN_k}
#' }
#'
#' @family Classification
#' @family Supervised Learning
#'
#' @export
npv <- function(...) {
  UseMethod(
    generic = "npv",
    object  = ..1
  )
}

#' @rdname npv
#' @export
weighted.npv <- function(...) {
  UseMethod(
    generic = "weighted.npv",
    object  = ..1
  )
}

# script end;
