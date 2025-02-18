# script: Relative Root Mean Squared Error
# date: 2024-12-27
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate Errors
# script start;

#' @inherit huberloss
#' 
#' @title Relative Root Mean Squared Error
#'
#' @description
#' The [rrmse()]-function computes the [Relative Root Mean Squared Error](https://en.wikipedia.org/wiki/Root-mean-square_deviation) between
#' the observed and predicted <[numeric]> vectors. The [weighted.rrmse()] function computes the weighted Relative Root Mean Squared Error.
#'
#' @usage
#' ## Generic S3 method
#' rrmse(
#'  actual,
#'  predicted,
#'  normalization = 1,
#'  ...
#' )
#' 
#' @param normalization A <[numeric]>-value of [length] \eqn{1} (default: \eqn{1}). \eqn{0}: [mean]-normalization, \eqn{1}: [range]-normalization, \eqn{2}: [IQR]-normalization.
#' 
#' @section Definition:
#'
#' The metric is calculated as,
#'
#' \deqn{
#'   \frac{RMSE}{\gamma}
#' }
#'
#' Where \eqn{\gamma} is the normalization factor.
#'
#' @example man/examples/scr_RelativeRootMeanSquaredError.R
#'
#' @family Regression
#' @family Supervised Learning
#' 
#' @export
rrmse <- function(
  actual,
  predicted,
  normalization = 1,
  ...) {
  UseMethod(
    generic = "rrmse"
  )
}

#' @rdname rrmse
#' @usage
#' ## Generic S3 method
#' weighted.rrmse(
#'  actual,
#'  predicted,
#'  w,
#'  normalization = 1,
#'  ...
#' )
#' @export
weighted.rrmse <- function(
  actual,
  predicted,
  w,
  normalization = 1,
  ...) {
  UseMethod(
    generic = "weighted.rrmse"
  )
}

# script end;
