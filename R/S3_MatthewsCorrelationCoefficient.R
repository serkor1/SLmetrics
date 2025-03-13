# script: Matthews Correlation Coefficient
# date: 2024-10-06
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate MCC methods
# script start;

#' @aliases mcc phi
#' @inherit accuracy
#' 
#' @title Matthews Correlation Coefficient
#'
#' @description
#' The [mcc()]-function computes the [Matthews Correlation Coefficient](https://en.wikipedia.org/wiki/Matthews_correlation_coefficient) (MCC), also known as the \eqn{\phi}-coefficient, between
#' two vectors of predicted and observed [factor()] values. The [weighted.mcc()] function computes the weighted Matthews Correlation Coefficient.
#'
#' @usage
#' ## Generic S3 method
#' mcc(...)
#' 
#' @section Definition:
#'
#' The metric is calculated as follows,
#'
#' \deqn{
#'   \frac{\#TP \times \#TN - \#FP \times \#FN}{\sqrt{(\#TP + \#FP)(\#TP + \#FN)(\#TN + \#FP)(\#TN + \#FN)}}
#' }
#' 
#' @example man/examples/scr_MatthewsCorrelationCoefficient.R
#'
#' @family Classification
#' @family Supervised Learning
#'
#' @export
mcc <- function(...) {
  UseMethod(
    generic = "mcc",
    object = ..1
  )
}

#' @rdname mcc
#' @usage
#' ## Generic S3 method
#' weighted.mcc(
#'  ...,
#'  w
#' )
#' @export
weighted.mcc <- function(
  ..., 
  w) {
  UseMethod(
    generic = "weighted.mcc",
    object = ..1
  )
}

#' @rdname mcc
#' @usage
#' ## Generic S3 method
#' phi(...)
#' 
#' @export
phi <- function(...) {
  UseMethod(
    generic = "phi",
    object = ..1
  )
}

#' @rdname mcc
#' @usage
#' ## Generic S3 method
#' weighted.phi(
#'  ...,
#'  w
#' )
#' @export
weighted.phi <- function(
  ...,
  w) {
  UseMethod(
    generic = "weighted.phi",
    object = ..1
  )
}

# script end;
