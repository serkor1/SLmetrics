# script: Coefficient of Determination
# date: 2024-10-10
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate Methods
# script start;

#' Compute the \eqn{R^2}
#'
#' @description
#' The [rsq()]-function calculates the \eqn{R^2}, the [coefficient of determination](https://en.wikipedia.org/wiki/Coefficient_of_determination), between the ovserved
#' and predicted <[numeric]> vectors. By default [rsq()] returns the unadjusted \eqn{R^2}. For adjusted \eqn{R^2} set \eqn{k = \kappa - 1}, where \eqn{\kappa} is the number of parameters.
#'
#' @inherit huberloss
#' @param k A <[numeric]>-vector of [length] 1. 0 by default. If \eqn{k>0}
#' the function returns the adjusted \eqn{R^2}.
#'
#' @section Calculation:
#'
#' The metric is calculated as follows,
#'
#' \deqn{
#'   R^2 = 1 - \frac{\text{SSE}}{\text{SST}} \frac{n-1}{n - (k + 1)}
#' }
#'
#' Where \eqn{\text{SSE}} is the sum of squared errors, \eqn{\text{SST}} is total sum of squared errors, \eqn{n} is the number of observations, and \eqn{k} is the number of non-constant parameters.
#'
#' @example man/examples/scr_CoefficientOfDetermination.R
#' 
#' @family regression
#' @export
rsq <- function(...) {
  UseMethod(
    generic = "rsq",
    object  = ..1
  )
}

#' @rdname rsq
#' @export
weighted.rsq <- function(...) {
  UseMethod(
    generic = "weighted.rsq",
    object  = ..1
  )
}

# script end;
