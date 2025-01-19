# script: Mean Absolute Percentage Error
# date: 2024-10-10
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate Methods
# script start;

#' Compute the \eqn{\text{mean}} \eqn{\text{absolute}} \eqn{\text{percentage}} \eqn{\text{error}}
#'
#' The [mape()]-function computes the [mean absolute percentage error](https://en.wikipedia.org/wiki/Mean_absolute_percentage_error) between
#' the observed and predicted <[numeric]> vectors. The [weighted.mape()] function computes the weighted mean absolute percentage error.
#'
#'
#' @inherit huberloss
#'
#' @example man/examples/scr_MeanAbsolutePercentageError.R
#'
#' @section Definition:
#'
#' The metric is calculated as,
#'
#' \deqn{
#'   \frac{1}{n} \sum_i^n \frac{|y_i - \upsilon_i|}{|y_i|}
#' }
#' 
#' @family Regression
#' @family Supervised Learning
#' @export
mape <- function(...) {
  UseMethod(
    generic = "mape",
    object  = ..1
  )
}

#' @rdname mape
#' @export
weighted.mape <- function(...) {
  UseMethod(
    generic = "weighted.mape",
    object  = ..1
  )
}

# script end;
