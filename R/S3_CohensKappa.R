# script: Cohen's Kappa
# date: 2024-10-07
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate Methods
# script start;

#' Compute Cohen's \eqn{\kappa}-statistic
#'
#' @description
#' The [kappa()]-function computes [Cohen's \eqn{\kappa}](https://en.wikipedia.org/wiki/Cohen%27s_kappa), a statistic that measures inter-rater agreement for categorical items between
#' two vectors of predicted and observed [factor()] values.
#'
#' If \eqn{\beta \neq 0} the off-diagonals of the confusion matrix are penalized with a factor of
#' \eqn{(y_{+} - y_{i,-})^\beta}. See below for further details.
#'
#'
#' @example man/examples/scr_kappa.R
#'
#' @inherit specificity
#'
#' @inheritParams specificity
#' @param beta A <[numeric]> value of [length] 1. 0 by default. If set to a value different from zero, the off-diagonal confusion matrix will be penalized.
#'
#'
#' @section Calculation
#' @family classification
#' @export
ckappa <- function(...) {
  UseMethod(
    generic = "ckappa",
    object  = ..1
  )
}

#' @rdname ckappa
#' @export
weighted.ckappa <- function(...) {
  UseMethod(
    generic = "weighted.ckappa",
    object  = ..1
  )
}


# script end;
