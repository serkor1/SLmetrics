# script: Mean Absolute Error
# date: 2024-10-10
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate Methods
# script start;

#' Compute the \eqn{\text{mean}} \eqn{\text{absolute}} \eqn{\text{error}}
#'
#' The [mae()]-function computes the simple and weighted [mean absolute error](https://en.wikipedia.org/wiki/Mean_absolute_error) between
#' the observed and predicted <[numeric]> vectors. If `w` is not [NULL] the function returns the weighted mean absolute error.
#'
#' @inherit huberloss
#'
#' @example man/examples/scr_mae.R
#'
#' @section Calculation:
#'
#' The metric is calulated as follows,
#'
#' \deqn{
#'   \frac{\sum_i^n |y_i - \upsilon_i|}{n}
#' }
#'
#' If \eqn{w} is not [NULL] the function returns the weigthed version.
#'
#' @family regression
#'
#' @export
mae <- function(...) {
  UseMethod(
    generic = "mae",
    object  = ..1
  )
}

#' @rdname mae
#' @export
weighted.mae <- function(...) {
  UseMethod(
    generic = "weighted.mae",
    object  = ..1
  )
}

# script end;
