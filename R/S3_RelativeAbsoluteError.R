# script: Relative Absolute Error
# date: 2024-10-11
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate Methods
# script start;

#' Compute the \eqn{\text{relative}} \eqn{\text{absolute}} \eqn{\text{error}}
#'
#' @description
#' The [rae()]-function calculates the normalized [relative absolute error](https://www.statisticshowto.com/relative-absolute-error/) between
#' the predicted and observed <[numeric]> vectors. If `w` is not [NULL] the function returns the weighted averages.
#'
#'
#' @inherit huberloss
#'
#' @section Calculation:
#'
#' The Relative Absolute Error (RAE) is calculated as:
#'
#' \deqn{
#'   \text{RAE} = \frac{\sum_{i=1}^n |y_i - \upsilon_i|}{\sum_{i=1}^n |y_i - \bar{y}|}
#' }
#'
#' Where \eqn{y_i} are the `actual` values, \eqn{\upsilon_i} are the `predicted` values,
#' and \eqn{\bar{y}} is the mean of the `actual` values.
#'
#' If weights \eqn{w_i} are provided, the Weighted RAE is calculated as:
#'
#' \deqn{
#'   \text{Weighted RAE} = \frac{\sum_{i=1}^n w_i |y_i - \upsilon_i|}{\sum_{i=1}^n w_i |y_i - \bar{y}_w|}
#' }
#'
#' Where \eqn{\bar{y}_w} is the weighted mean of the `actual` values, calculated as:
#' \deqn{
#'   \bar{y}_w = \frac{\sum_{i=1}^n w_i y_i}{\sum_{i=1}^n w_i}
#' }
#'
#' This metric provides a relative measure by comparing the total absolute prediction error to the total absolute deviation from the mean of the actual values.
#'
#' @example man/examples/scr_RelativeAbsoluteError.R
#' @family Regression
#' @family Supervised Learning
#' @export
rae <- function(...) {
  UseMethod(
    generic = "rae",
    object  = ..1
  )
}

#' @rdname rae
#' @export
weighted.rae <- function(...) {
  UseMethod(
    generic = "weighted.rae",
    object  = ..1
  )
}

# script end;
