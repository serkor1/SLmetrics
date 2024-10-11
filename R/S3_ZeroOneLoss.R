# script: Zero-One Loss
# date: 2024-10-08
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate Methods
# script start;


#' Compute the \eqn{\text{Zero}}-\eqn{\text{One}} \eqn{\text{Loss}}
#'
#' @description
#' The [zerooneloss()]-function computes the [Zero-One Loss](https://en.wikipedia.org/wiki/Loss_functions_for_classification), a classification loss function that calculates the proportion of misclassified instances between
#' two vectors of predicted and observed [factor()] values.
#'
#' @inherit specificity
#'
#' @section Calculation:
#'
#' Zero-One Loss is a global metric that measures the proportion of incorrect predictions made by the model. It is calculated as follows,
#'
#' \deqn{
#'   \frac{\#FP + \#FN}{\#TP + \#TN + \#FP + \#FN}
#' }
#'
#' Where \eqn{\#TP}, \eqn{\#TN}, \eqn{\#FP}, and \eqn{\#FN} represent the true positives, true negatives, false positives, and false negatives, respectively.
#'
#' Zero-One Loss provides an overall measure of the model's prediction errors across all classes.
#'
#' @returns
#'
#' A <[numeric]>-vector of [length] 1
#'
#' @example man/examples/scr_zerooneloss.R
#'
#' @family classification
#'
#' @export
zerooneloss <- function(...) {
  UseMethod(
    generic = "zerooneloss",
    object  = ..1
  )
}

# script end;
