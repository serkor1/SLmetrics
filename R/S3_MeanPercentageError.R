# script: Mean Percentage Error
# date: 2024-10-10
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate Methods
# script start;

#' Compute the \eqn{\text{mean}} \eqn{\text{percentage}} \eqn{\text{error}}
#'
#' The [mpe()]-function computes the [mean percentage error](https://en.wikipedia.org/wiki/Mean_percentage_error) between
#' the observed and predicted <[numeric]> vectors. If `w` is not [NULL], the function returns the weighted mean percentage error.
#'
#' @inherit huberloss
#'
#' @example man/examples/scr_MeanPercentageError.R
#'
#' @section Calculation:
#'
#' The metric is calculated as,
#'
#' \deqn{
#'   \frac{1}{n} \sum_i^n \frac{y_i - \upsilon_i}{y_i}
#' }
#'
#' Where \eqn{y_i} and \eqn{\upsilon_i} are the `actual` and `predicted` values respectively. If \eqn{\text{w}} is not [NULL], the weighted version is calculated.
#'
#' @family Regression
#' @family Supervised Learning
#' @export
mpe <- function(...) {
  UseMethod(
    generic = "mpe",
    object  = ..1
  )
}

#' @rdname mpe
#' @export
weighted.mpe <- function(...) {
  UseMethod(
    generic = "weighted.mpe",
    object  = ..1
  )
}

# script end;
