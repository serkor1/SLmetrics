# script: Coefficient of Determination
# date: 2024-10-10
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate Methods
# script start;

#' @inherit huberloss
#' 
#' @title \eqn{R^2}
#'
#' @description
#' A generic function for the [\eqn{R^2}](https://en.wikipedia.org/wiki/Coefficient_of_determination). The unadjusted [\eqn{R^2}](https://en.wikipedia.org/wiki/Coefficient_of_determination) is returned by default.
#' Use [weighted.rsq()] for the weiighted [\eqn{R^2}](https://en.wikipedia.org/wiki/Coefficient_of_determination).
#'
#' @usage
#' ## Generic S3 method
#' rsq(
#'  ...,
#'  k = 0
#' )
#' 
#' @param k A <[numeric]>-vector of [length] 1 (default: 0). For adjusted \eqn{R^2} set \eqn{k = \kappa - 1}, where \eqn{\kappa} is the number of parameters.
#'
#' @section Definition:
#' Let \eqn{R^2 \in [-\infty, 1]} be the explained variation. The \eqn{R^2} is calculated as,
#'
#' \deqn{
#'   R^2 = 1 - \frac{\sum{(y_i - \hat{y}_i)^2}}{\sum{(y_i-\bar{y})^2}} \frac{n-1}{n - (k + 1)}
#' }
#'
#' Where:
#' 
#' - \eqn{n} is the number of observations
#' - \eqn{k} is the number of features
#' - \eqn{y} is the actual values
#' - \eqn{\hat{y}_i} is the predicted values
#' - \eqn{\sum{(y_i - \hat{y}_i)^2}} is the sum of squared errors and,
#' - \eqn{\sum{(y_i-\bar{y})^2}} is total sum of squared errors
#'
#' @example man/examples/scr_CoefficientOfDetermination.R
#' 
#' @family Regression
#' @family Supervised Learning
#' @export
rsq <- function(
  ..., 
  k = 0) {
  UseMethod(
    generic = "rsq",
    object  = ..1
  )
}

#' @rdname rsq
#' @usage
#' ## Generic S3 method
#' weighted.rsq(
#'  ...,
#'  w,
#'  k = 0
#' )
#' @export
weighted.rsq <- function(
  ...,
  w,
  k = 0) {
  UseMethod(
    generic = "weighted.rsq",
    object  = ..1
  )
}

# script end;
