# script: Mean Squared Error
# date: 2024-10-09
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate Errors
# script start;

#' Compute the \eqn{\text{mean}} \eqn{\text{squared}} \eqn{\text{error}}
#'
#' The [mse()]-function computes the simple and weighted [mean squared error](https://en.wikipedia.org/wiki/Mean_squared_error) between
#' the observed and predicted <[numeric]> vectors. If `w` is not [NULL], the function returns the weighted mean squared error.
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
#' Where \eqn{y_i} and \eqn{\upsilon_i} are the `actual` and `predicted` values respectively. If \eqn{\text{w}} is not [NULL], the weighted version is calculated.
#'
#' @family regression
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
