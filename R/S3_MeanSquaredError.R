# script: Mean Squared Error
# date: 2024-10-09
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate Errors
# script start;

#' @inherit huberloss
#'
#' @title Mean Squared Error
#'
#' @description
#' The [mse()]-function computes the [mean squared error](https://en.wikipedia.org/wiki/Mean_squared_error) between
#' the observed and predicted <[numeric]> vectors. The [weighted.mse()] function computes the weighted mean squared error.
#' 
#' @usage
#' ## Generic S3 method
#' mse(
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
#'   \frac{1}{n} \sum_i^n (y_i - \upsilon_i)^2
#' }
#'
#' Where \eqn{y_i} and \eqn{\upsilon_i} are the `actual` and `predicted` values respectively. 
#' 
#' @example man/examples/scr_MeanSquaredError.R
#'
#' @family Regression
#' @family Supervised Learning
#' 
#' @export
mse <- function( 
  actual, 
  predicted,
  ...) {
  UseMethod(
    generic = "mse"
  )
}

#' @rdname mse
#' @usage
#' ## Generic S3 method
#' weighted.mse(
#'  actual,
#'  predicted,
#'  w,
#'  ...
#' )
#' @export
weighted.mse <- function(
  actual, 
  predicted,
  w,
  ...) {
  UseMethod(
    generic = "weighted.mse"
  )
}

# script end;
