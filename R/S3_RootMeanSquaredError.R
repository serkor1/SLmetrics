# script: Root Mean Squared Error
# date: 2024-10-09
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate Errors
# script start;

#' Compute the \eqn{\text{root mean squared error}}
#'
#' The [rmse()]-function computes the simple and weighted [root mean squared error](https://en.wikipedia.org/wiki/Root-mean-square_deviation) between
#' the observed and predicted <[numeric]> vectors. If `w` is not [NULL], the function returns the weighted root mean squared error.
#'
#' @inherit huberloss
#'
#' @example man/examples/scr_rmse.R
#'
#' @section Calculation:
#'
#' The metric is calculated as,
#'
#' \deqn{
#'   \sqrt{\frac{1}{n} \sum_i^n (y_i - \upsilon_i)^2}
#' }
#'
#' Where \eqn{y_i} and \eqn{\upsilon_i} are the `actual` and `predicted` values respectively. If \eqn{\text{w}} is not [NULL], the weighted version is calculated.
#'
#' @family regression
#' @export
rmse <- function(...) {
  UseMethod(
    generic = "rmse",
    object  = ..1
  )
}

# script end;
