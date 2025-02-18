# script: Relative Absolute Error
# date: 2024-10-11
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate Methods
# script start;

#' @inherit huberloss
#'
#' @title Relative Absolute Error
#'
#' @description
#' The [rae()]-function calculates the normalized [relative absolute error](https://www.statisticshowto.com/relative-absolute-error/) between
#' the predicted and observed <[numeric]> vectors. The [weighted.rae()] function computes the weigthed relative absolute error.
#'
#' @usage
#' ## Generic S3 method
#' rae(
#'  actual,
#'  predicted,
#'  ...
#' )
#' 
#' @section Definition:
#'
#' The Relative Absolute Error (RAE) is calculated as:
#'
#' \deqn{
#'   \text{RAE} = \frac{\sum_{i=1}^n |y_i - \upsilon_i|}{\sum_{i=1}^n |y_i - \bar{y}|}
#' }
#'
#' Where \eqn{y_i} are the `actual` values, \eqn{\upsilon_i} are the `predicted` values,
#' and \eqn{\bar{y}} is the mean of the `actual` values.
#' 
#' @example man/examples/scr_RelativeAbsoluteError.R
#' 
#' @family Regression
#' @family Supervised Learning
#' 
#' @export
rae <- function(
  actual,
  predicted,
  ...) {
  UseMethod(
    generic = "rae"
  )
}

#' @rdname rae
#' @usage
#' ## Generic S3 method
#' weighted.rae(
#'  actual,
#'  predicted,
#'  w,
#'  ...
#' )
#' @export
weighted.rae <- function(
  actual,
  predicted,
  w,
  ...) {
  UseMethod(
    generic = "weighted.rae"
  )
}

# script end;
