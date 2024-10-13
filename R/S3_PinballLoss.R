# script: Pinball Loss
# date: 2024-10-13
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate Methods
# script start;

#' @title Compute the \eqn{\text{pinball}} \eqn{\text{loss}}
#'
#' @description
#' The [pinball()]-function computes the [pinball loss](https://en.wikipedia.org/wiki/Quantile_regression) between
#' the observed and predicted <[numeric]> vectors. If If `w` is not [NULL], the function returns the weighted pinball loss.
#'
#' @inherit huberloss
#' @param alpha A <[numeric]>-value of [length] 1. The slope of the pinball loss function. \eqn{0.5} by default.
#'
#' @example man/examples/scr_pinball.R
#' @section Calculation:
#'
#'
#' @family regression
#' @export
pinball <- function(...) {
  UseMethod(
    generic = "pinball",
    object  = ..1
  )
}

# script end;
