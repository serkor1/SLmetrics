# script: Mean Squared Error
# date: 2024-10-09
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate Errors
# script start;

#' Compute the \eqn{\text{mean}} \eqn{\text{squared}} \eqn{\text{error}}
#'
#' The [mse()]-function computes the [mean squared error](https://en.wikipedia.org/wiki/Mean_squared_error) between
#' the observed and predicted <[numeric]> vectors. The [weighted.mse()] function computes the weighted mean squared error.
#'
#' @inherit huberloss
#'
#' @example man/examples/scr_MeanSquaredError.R
#'
#' @section Calculation:
#'
#' The metric is calculated as,
#'
#' \deqn{
#'   \frac{1}{n} \sum_i^n (y_i - \upsilon_i)^2
#' }
#'
#' Where \eqn{y_i} and \eqn{\upsilon_i} are the `actual` and `predicted` values respectively. 
#' 
#' @family Regression
#' @family Supervised Learning
#' @export
mse <- function(...) {
  UseMethod(
    generic = "mse",
    object  = ..1
  )
}

#' @rdname mse
#' @export
weighted.mse <- function(...) {
  UseMethod(
    generic = "weighted.mse",
    object  = ..1
  )
}

# script end;
