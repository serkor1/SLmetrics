# script: Hamming Loss
# date: 2025-08-04
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate Methods
# script start;

#' @inherit accuracy
#'
#' @title Hamming Loss
#'
#' @description
#' The [zerooneloss()]-function computes the [zero-one Loss](https://en.wikipedia.org/wiki/Loss_functions_for_classification), a classification loss function that calculates the proportion of misclassified instances between
#' two vectors of predicted and observed [factor()] values. The [weighted.zerooneloss()] function computes the weighted zero-one loss.
#' 
#' @usage
#' ## Generic S3 method
#' hammingloss(...)
#' 
#' @section Definition:
#'
#' The metric is calculated as follows,
#'
#' \deqn{
#'   \frac{\#FP + \#FN}{\#TP + \#TN + \#FP + \#FN}
#' }
#'
#' Where \eqn{\#TP}, \eqn{\#TN}, \eqn{\#FP}, and \eqn{\#FN} represent the true positives, true negatives, false positives, and false negatives, respectively.
#'
#' @example man/examples/scr_HammingLoss.R
#'
#' @family Classification
#' @family Supervised Learning
#'
#' @export
hammingloss <- function(...) {
  UseMethod(
    generic = "hammingloss",
    object  = ..1
  )
}

#' @rdname hammingloss
#' @usage
#' ## Generic S3 method
#' weighted.hammingloss(
#'  ...,
#'  w
#' )
#' @export
weighted.hammingloss <- function(
  ...,
  w) {
  UseMethod(
    generic = "weighted.hammingloss",
    object  = ..1
  )
}

# script end;
