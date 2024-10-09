# script: Matthews Correlation Coefficient
# date: 2024-10-06
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate MCC methods
# script start;

#' Compute the \eqn{\text{Matthews}} \eqn{\text{Correlation}} \eqn{\text{Coefficient}}
#'
#' @description
#' The [mcc()]-function computes the [Matthews Correlation Coefficient](https://en.wikipedia.org/wiki/Matthews_correlation_coefficient) (MCC), also known as the \eqn{\phi}-coefficient, between
#' two vectors of predicted and observed [factor()] values.
#'
#' @example man/examples/scr_mcc.R
#'
#' @inherit precision
#'
#' @section Calculation:
#'
#' The metric is calculated as follows,
#'
#' \deqn{
#'   \frac{\#TP \times \#TN - \#FP \times \#FN}{\sqrt{(\#TP + \#FP)(\#TP + \#FN)(\#TN + \#FP)(\#TN + \#FN)}}
#' }
#'
#'
#' @returns
#' A named <[numeric]> vector of length k
#'
#' @family classification
#'
#' @aliases mcc phi
#'
#' @export
mcc <- function(...) {
  UseMethod(
    generic = "mcc",
    object  = ..1
  )
}

#' @rdname mcc
#' @export
phi <- function(...) {
  UseMethod(
    generic = "phi",
    object  = ..1
  )
}

# script end;
