# script: Zero-One Loss
# date: 2024-10-08
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate Methods
# script start;

#' @inherit accuracy
#'
#' @title Zero-One Loss
#'
#' @description
#' The [zerooneloss()]-function computes the [zero-one Loss](https://en.wikipedia.org/wiki/Loss_functions_for_classification), a classification loss function that calculates the proportion of misclassified instances between
#' two vectors of predicted and observed [factor()] values. The [weighted.zerooneloss()] function computes the weighted zero-one loss.
#' 
#' @usage
#' ## Generic S3 method
#' zerooneloss(...)
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
#' @example man/examples/scr_ZeroOneLoss.R
#'
#' @family Classification
#' @family Supervised Learning
#'
#' @export
zerooneloss <- function(...) {
  UseMethod(
    generic = "zerooneloss",
    object  = ..1
  )
}

#' @rdname zerooneloss
#' @usage
#' ## Generic S3 method
#' weighted.zerooneloss(
#'  ...,
#'  w
#' )
#' @export
weighted.zerooneloss <- function(
  ...,
  w) {
  UseMethod(
    generic = "weighted.zerooneloss",
    object  = ..1
  )
}

# script end;
