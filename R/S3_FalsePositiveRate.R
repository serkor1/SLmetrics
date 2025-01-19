# script: False Positive Rate
# date: 2024-10-07
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate Methods
# for False Positive Rate
# script start;

#' Compute the \eqn{\text{false}} \eqn{\text{positive}} \eqn{\text{rate}}
#'
#' @description
#' The [fpr()]-function computes the [False Positive Rate](https://en.wikipedia.org/wiki/False_positive_rate) (FPR), also known as the fall-out ([fallout()]), between
#' two vectors of predicted and observed [factor()] values. The [weighted.fpr()] function computes the weighted false positive rate.
#'
#' @inherit specificity
#'
#' @example man/examples/scr_FalsePositiveRate.R
#'
#' @section Definition:
#'
#' The metric is calculated for each class \eqn{k} as follows,
#'
#' \deqn{
#'   \frac{\#FP_k}{\#FP_k + \#TN_k}
#' }
#'
#' Where \eqn{\#FP_k} and \eqn{\#TN_k} represent the number of false positives and true negatives, respectively, for each class \eqn{k}.
#' 
#' @family Classification
#' @family Supervised Learning
#'
#' @aliases fpr fallout
#'
#' @export
fpr <- function(...) {
  UseMethod(
    generic = "fpr",
    object  = ..1
  )
}

#' @rdname fpr
#' @export
fallout <- function(...) {
  UseMethod(
    generic = "fallout",
    object  = ..1
  )
}

#' @rdname fpr
#' @export
weighted.fpr <- function(...) {
  UseMethod(
    generic = "weighted.fpr",
    object  = ..1
  )
}

#' @rdname fpr
#' @export
weighted.fallout <- function(...) {
  UseMethod(
    generic = "weighted.fallout",
    object  = ..1
  )
}
# script end;
