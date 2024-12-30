# script: Relative Root Mean Squared Error
# date: 2024-12-27
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate Errors
# script start;

#' Compute the \eqn{\text{relative}} \eqn{\text{root}} \eqn{\text{mean}} \eqn{\text{squared}} \eqn{\text{error}}
#'
#' The [rrmse()]-function computes the [Relative Root Mean Squared Error](https://en.wikipedia.org/wiki/Root-mean-square_deviation) between
#' the observed and predicted <[numeric]> vectors. The [weighted.rrmse()] function computes the weighted Relative Root Mean Squared Error.
#'
#' @inherit huberloss
#' @param normalization A <[numeric]>-value of [length] \eqn{1} (default: \eqn{1}). \eqn{0}: [mean]-normalization, \eqn{1}: [range]-normalization, \eqn{2}: [IQR]-normalization.
#'
#' @example man/examples/scr_RelativeRootMeanSquaredError.R
#'
#' @section Calculation:
#'
#' The metric is calculated as,
#'
#' \deqn{
#'   \frac{RMSE}{\gamma}
#' }
#'
#' Where \eqn{\gamma} is the normalization factor.
#'
#' @family Regression
#' @family Supervised Learning
#' @export
rrmse <- function(...) {
  UseMethod(
    generic = "rrmse",
    object  = ..1
  )
}

#' @rdname rrmse
#' @export
weighted.rrmse <- function(...) {
  UseMethod(
    generic = "weighted.rrmse",
    object  = ..1
  )
}

# script end;
