# script: Root Mean Squared Logarithmic Error
# date: 2024-10-09
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate Methods
# script start;

#' Compute the \eqn{\text{root}} \eqn{\text{mean}} \eqn{\text{squared}} \eqn{\text{logarithmic}} \eqn{\text{error}}
#'
#' The [rmsle()]-function computes the root mean squared logarithmic error between the observed and predicted <[numeric]> vectors. The [weighted.rmsle()] function computes the weighted root mean squared logarithmic error.
#'
#' @inherit huberloss
#'
#' @example man/examples/scr_RootMeanSquaredLogarithmicError.R
#'
#' @section Calculation:
#'
#' The metric is calculated as,
#'
#' \deqn{
#'   \sqrt{\frac{1}{n} \sum_i^n (\log(1 + y_i) - \log(1 + \upsilon_i))^2}
#' }
#'
#' Where \eqn{y_i} and \eqn{\upsilon_i} are the `actual` and `predicted` values respectively. 
#' 
#' @family Regression
#' @family Supervised Learning
#' 
#' @export
rmsle <- function(...) {
  UseMethod(
    generic = "rmsle",
    object  = ..1
  )
}

#' @rdname rmsle
#' @export
weighted.rmsle <- function(...) {
  UseMethod(
    generic = "weighted.rmsle",
    object  = ..1
  )
}

# script end;
