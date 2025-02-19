# script: Root Mean Squared Logarithmic Error
# date: 2024-10-09
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate Methods
# script start;

#' @inherit huberloss
#'
#' @title Root Mean Squared Logarithmic Error
#' 
#' @description
#' The [rmsle()]-function computes the root mean squared logarithmic error between the observed and predicted <[numeric]> vectors. The [weighted.rmsle()] function computes the weighted root mean squared logarithmic error.
#' 
#' @usage
#' ## Generic S3 method
#' rmsle(
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
#'   \sqrt{\frac{1}{n} \sum_i^n (\log(1 + y_i) - \log(1 + \upsilon_i))^2}
#' }
#'
#' Where \eqn{y_i} and \eqn{\upsilon_i} are the `actual` and `predicted` values respectively. 
#'
#' @example man/examples/scr_RootMeanSquaredLogarithmicError.R
#'
#' @family Regression
#' @family Supervised Learning
#' 
#' @export
rmsle <- function(
  actual,
  predicted,
  ...) {
  UseMethod(
    generic = "rmsle"
  )
}

#' @rdname rmsle
#' @usage
#' ## Generic S3 method
#' weighted.rmsle(
#'  actual,
#'  predicted,
#'  w,
#'  ...
#' )
#' @export
weighted.rmsle <- function(
  actual, 
  predicted, 
  w,
  ...) {
  UseMethod(
    generic = "weighted.rmsle"
  )
}

# script end;
