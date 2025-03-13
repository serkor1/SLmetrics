# script: Root Relative Squared Error
# date: 2024-10-11
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Genereate Methods
# script start;

#' @inherit huberloss
#'
#' @title Root Relative Squared Error
#'
#' @description
#' The [rrse()]-function calculates the [root relative  squared error](https://en.wikipedia.org/wiki/Root_mean_square_deviation) between
#' the predicted and observed <[numeric]> vectors. The [weighted.rrse()] function computes the weighed root relative squared errorr.
#' 
#' @usage
#' ## Generic S3 method
#' rrse(
#'  actual,
#'  predicted,
#'  ...
#' )
#'
#' @section Definition:
#'
#' The metric is calculated as,
#'
#' \deqn{
#'   \text{RRSE} = \sqrt{\frac{\sum_{i=1}^n (y_i - \upsilon_i)^2}{\sum_{i=1}^n (y_i - \bar{y})^2}}
#' }
#'
#' Where \eqn{y_i} are the `actual` values, \eqn{\upsilon_i} are the `predicted` values,
#' and \eqn{\bar{y}} is the mean of the `actual` values.
#'
#' @example man/examples/scr_RootRelativeSquaredError.R
#' 
#' @family Regression
#' @family Supervised Learning
#' 
#' @export
rrse <- function(
  actual,
  predicted,
  ...) {
  UseMethod(
    generic = "rrse"
  )
}

#' @rdname rrse
#' @usage
#' ## Generic S3 method
#' weighted.rrse(
#'  actual,
#'  predicted,
#'  w,
#'  ...
#' )
#' @export
weighted.rrse <- function(
  actual,
  predicted,
  w,
  ...) {
  UseMethod(
    generic = "weighted.rrse"
  )
}

# script end;
