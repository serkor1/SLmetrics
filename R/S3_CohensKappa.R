# script: Cohen's Kappa
# date: 2024-10-07
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate Methods
# script start;

#' @title NULL
#' @usage NULL
#' @return NULL
#' 
#' @templateVar .TITLE  Cohen's \eqn{\kappa}-statistic
#' @templateVar .FUN ckappa
#' @templateVar .TASK Classification
#' @templateVar .MULTI_OUTPUT false
#' @template classification_standard_template
#'
#' @export
ckappa <- function(...) {
  UseMethod(
    generic = "ckappa"
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
    generic = "weighted.ckappa"
  )
}

# script end;
