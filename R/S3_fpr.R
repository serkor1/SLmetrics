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
#' two vectors of predicted and observed [factor()] values.
#'
#' When `aggregate = TRUE`, the function returns the micro-average FPR across all classes \eqn{k}.
#' By default, it returns the class-wise FPR.
#'
#' @inherit specificity
#'
#' @example man/examples/scr_fpr.R
#'
#' @section Calculation:
#'
#' The metric is calculated for each class \eqn{k} as follows,
#'
#' \deqn{
#'   \frac{\#FP_k}{\#FP_k + \#TN_k}
#' }
#'
#' Where \eqn{\#FP_k} and \eqn{\#TN_k} represent the number of false positives and true negatives, respectively, for each class \eqn{k}.
#'
#' When `aggregate = TRUE`, the micro-average is calculated across all classes,
#'
#' \deqn{
#'   \frac{\sum_{k=1}^k \#FP_k}{\sum_{k=1}^k \#FP_k + \sum_{k=1}^k \#TN_k}
#' }
#'
#' The FPR is the complement of specificity, such that \eqn{\text{FPR} = 1 - \text{Specificity}}.
#'
#' @family classification
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
# script end;
