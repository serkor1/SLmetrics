# script: Accuracy
# date: 2024-10-05
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate methods for accuracy
# script start;

#' Compute the \eqn{\text{accuracy}}
#' 
#' @description
#'
#' The [accuracy()] function computes the [accuracy](https://en.wikipedia.org/wiki/Precision_and_recall) between two
#' vectors of predicted and observed [factor()] values. The [weighted.accuracy()] function computes the weighted accuracy.
#'
#' @param actual A vector of <[factor]>- of [length] \eqn{n}, and \eqn{k} levels
#' @param predicted A vector of <[factor]>-vector of [length] \eqn{n}, and \eqn{k} levels
#' @param w A <[numeric]>-vector of [length] \eqn{n}. [NULL] by default
#' @param x A confusion matrix created [cmatrix()]
#' 
#' @inherit specificity
#'
#' @section Calculation:
#'
#' The metric is calculated as follows,
#'
#' \deqn{
#'   \frac{\#TP + \#TN}{\#TP + \#TN + \#FP + \#FN}
#' }
#'
#' Where \eqn{\#TP}, \eqn{\#TN}, \eqn{\#FP}, and \eqn{\#FN} is the number of true positives, true negatives, false positives, and false negatives, respectively.
#'
#' @returns
#'
#' A <[numeric]>-vector of [length] 1
#'
#' @example man/examples/scr_Accuracy.R
#'
#' @family Classification
#' @family Supervised Learning
#' @export
accuracy <- function(...) {
  UseMethod(
    generic = "accuracy",
    object  = ..1
  )
}

#' @rdname accuracy
#' @export
weighted.accuracy <- function(...) {
  UseMethod(
    generic = "weighted.accuracy",
    object  = ..1
  )
}

# script end;
