# script: Cohen's Kappa
# date: 2024-10-07
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate Methods
# script start;

#' @inherit specificity
#' @inheritParams accuracy
#' 
#' @title Cohen's \eqn{\kappa}-statistic
#'
#' @description
#' A generic function for [Cohen's \eqn{\kappa}](https://en.wikipedia.org/wiki/Cohen%27s_kappa)-statistic. Use [weighted.ckappa()] for the weighted [\eqn{\kappa}](https://en.wikipedia.org/wiki/Cohen%27s_kappa)-statistic.
#'
#' @usage
#' ckappa(
#'  ...,
#'  beta = 0
#' )
#' 
#' @param beta A <[numeric]> value of [length] 1 (default: 0). If \eqn{\beta \neq 0} the off-diagonals of the confusion matrix are penalized with a factor of \eqn{(y_{+} - y_{i,-})^\beta}.
#' 
#' @section Definition:
#' Let \eqn{\kappa \in [0, 1]} be the inter-rater (intra-rater) reliability. The inter-rater (intra-rater) reliability is calculated as, 
#' 
#' \deqn{
#'   \kappa = \frac{\rho_p - \rho_e}{1-\rho_e}
#' }
#' 
#' Where:
#' 
#' - \eqn{\rho_p} is the empirical probability of agreement between predicted and actual values
#' - \eqn{\rho_e} is the expected probability of agreement under random chance
#' 
#' If \eqn{\beta \neq 0} the off-diagonals in the confusion matrix is penalized before \eqn{\rho} is calculated. More formally,
#' 
#' \deqn{
#'  \chi = X \circ Y^{\beta}
#' }
#' 
#' Where:
#' 
#' - \eqn{X} is the confusion matrix
#' - \eqn{Y} is the penalizing matrix and
#' - \eqn{\beta} is the penalizing factor
#'
#' @example man/examples/scr_CohensKappa.R
#' 
#' @family Classification
#' @family Supervised Learning
#' 
#' @export
ckappa <- function(
  ...,
  beta = 0) {
  UseMethod(
    generic = "ckappa",
    object  = ..1
  )
}

#' @rdname ckappa
#' @usage
#' weighted.ckappa(
#'  ...,
#'  w,
#'  beta = 0
#' )
#' @export
weighted.ckappa <- function(
  ...,
  w,
  beta = 0) {
  UseMethod(
    generic = "weighted.ckappa",
    object  = ..1
  )
}

# script end;
