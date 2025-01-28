# script: Root Mean Squared Error
# date: 2024-10-09
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate Errors
# script start;

#' @inherit huberloss
#'
#' @title Root Mean Squared Error
#'
#' @description 
#' The [rmse()]-function computes the [root mean squared error](https://en.wikipedia.org/wiki/Root-mean-square_deviation) between
#' the observed and predicted <[numeric]> vectors. The [weighted.rmse()] function computes the weighted root mean squared error.
#' 
#' @section Definition:
#'
#' The metric is calculated as,
#'
#' \deqn{
#'   \sqrt{\frac{1}{n} \sum_i^n (y_i - \upsilon_i)^2}
#' }
#'
#' Where \eqn{y_i} and \eqn{\upsilon_i} are the `actual` and `predicted` values respectively.
#'
#' @example man/examples/scr_RootMeanSquaredError.R
#'
#' @family Regression
#' @family Supervised Learning
#' 
#' @export
rmse <- function(...) {
  UseMethod(
    generic = "rmse",
    object  = ..1
  )
}

#' @rdname rmse
#' @export
weighted.rmse <- function(...) {
  UseMethod(
    generic = "weighted.rmse",
    object  = ..1
  )
}

# script end;
