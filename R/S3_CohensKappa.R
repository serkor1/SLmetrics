# script: Cohen's Kappa
# date: 2024-10-07
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate Methods
# script start;

#' Compute Cohen's \eqn{\kappa}-statistic
#'
#' @description
#' The [kappa()]-function computes [Cohen's \eqn{\kappa}](https://en.wikipedia.org/wiki/Cohen%27s_kappa), a statistic that measures inter-rater agreement for categorical items between
#' two vectors of predicted and observed [factor()] values. The [weighted.ckappa()] function computes the weighted \eqn{\kappa}-statistic.
#'
#' If \eqn{\beta \neq 0} the off-diagonals of the confusion matrix are penalized with a factor of
#' \eqn{(y_{+} - y_{i,-})^\beta}. See below for further details.
#'
#' @inherit specificity
#'
#' @inheritParams accurracy
#' @param beta A <[numeric]> value of [length] 1 (default: 0). If set to a value different from zero, the off-diagonal confusion matrix will be penalized.
#'
#' @example man/examples/scr_CohensKappa.R
#' 
#' @section Definition:
#' 
#' \deqn{
#'   \frac{\rho_p - \rho_e}{1-\rho_e}
#' }
#' 
#' where \eqn{\rho_p} is the empirical probability of agreement between predicted and actual values, and \eqn{\rho_e} is the expected probability of agreement under random chance.
#' 
#' 
#' @family Classification
#' @family Supervised Learning
#' 
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
