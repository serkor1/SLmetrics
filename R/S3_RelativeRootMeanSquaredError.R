# script: Relative Root Mean Squared Error
# date: 2024-10-11
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Genereate Methods
# script start;

#' Compute the \eqn{\text{relative}} \eqn{\text{root}} \eqn{\text{mean}} \eqn{\text{squared}}  \eqn{\text{error}}
#'
#' @description
#' The [rrmse()]-function calculates the normalized [root mean squared error](https://en.wikipedia.org/wiki/Root_mean_square_deviation) between
#' the predicted and observed <[numeric]> vectors. The [weighted.rrmse()] function computes the weighed relative root mean squared error.
#'
#' @inherit huberloss
#'
#' @section Calculation:
#'
#' The Relative Root Mean Squared Error (RRMSE) is calculated as:
#'
#' \deqn{
#'   \text{RRSE} = \sqrt{\frac{\sum_{i=1}^n (y_i - \upsilon_i)^2}{\sum_{i=1}^n (y_i - \bar{y})^2}}
#' }
#'
#' Where \eqn{y_i} are the `actual` values, \eqn{\upsilon_i} are the `predicted` values,
#' and \eqn{\bar{y}} is the mean of the `actual` values.
#'
#' @example man/examples/scr_RelativeRootMeanSquaredError.R
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
