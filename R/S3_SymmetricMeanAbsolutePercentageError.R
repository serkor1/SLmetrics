# script:Symmetric Mean Absolute Error
# date: 2024-10-10
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate Methods
# script start;

#' Compute the \eqn{\text{symmetric}} \eqn{\text{mean}} \eqn{\text{absolute}} \eqn{\text{percentage}} \eqn{\text{error}}
#'
#' The [smape()]-function computes the  [symmetric mean absolute percentage error](https://en.wikipedia.org/wiki/Symmetric_mean_absolute_percentage_error) between
#' the observed and predicted <[numeric]> vectors. The [weighted.smape()] function computes the weighted symmetric mean absolute percentage error.
#' 
#' @inherit huberloss
#'
#' @example man/examples/scr_SymmetricMeanAbsolutePercentageError.R
#'
#' @section Calculation:
#'
#' The metric is calculated as follows,
#'
#' \deqn{
#'   \sum_i^n \frac{1}{n} \frac{|y_i - \upsilon_i|}{\frac{|y_i|+|\upsilon_i|}{2}}
#' }
#'
#' where \eqn{y_i} and \eqn{\upsilon_i} is the `actual` and `predicted` values respectively.
#' 
#'
#' @family Regression
#' @family Supervised Learning
#' @export
smape <- function(...) {
  UseMethod(
    generic = "smape",
    object  = ..1
  )
}

#' @rdname smape
#' @export
weighted.smape <- function(...) {
  UseMethod(
    generic = "weighted.smape",
    object  = ..1
  )
}


# script end;
