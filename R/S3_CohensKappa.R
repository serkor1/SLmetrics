# script: Cohen's Kappa
# date: 2024-10-07
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate Methods
# script start;

#' @templateVar .TITLE  Cohen's \eqn{\kappa} statistic
#' @templateVar .FUN ckappa
#' @templateVar .TASK Classification
#' @template classification_inheritDotParams
#' @template classification_factor_example
#' @template classification_cmatrix_template
#' @usage
#' ## Generic S3 method
#' ## for unweighted Cohen's
#' ## Kappa statistic
#' ckappa(...)
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
#' @usage
#' ## Generic S3 method
#' ## for weighted Cohen's
#' ## Kappa statistic
#' weighted.ckappa(...)
#' @export
weighted.ckappa <- function(...) {
  UseMethod(
    generic = "weighted.ckappa",
    object  = ..1
  )
}

# script end;
