# script: Cohen's Kappa
# date: 2024-10-07
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate Methods
# script start;

#' @title NULL
#' @usage NULL
#' @returns NULL
#' 
#' @templateVar .TITLE  Cohen's \eqn{\kappa}-statistic
#' @templateVar .FUN ckappa
#' @templateVar .TASK Classification
#' @templateVar .MULTI_OUTPUT false
#' 
#' @template generic_description
#' @template classification_standard_template
#'
#' @export
ckappa <- function(...) {
  UseMethod(
    generic = "ckappa"
  )
}

#' @usage NULL
#' 
#' @templateVar .TITLE Cohen's \eqn{\kappa}-statistic
#' @templateVar .FUN ckappa
#' @templateVar .TASK Classification
#' 
#' @template generic_inherit
#' 
#' @export
weighted.ckappa <- function(...) {
  UseMethod(
    generic = "weighted.ckappa"
  )
}

# script end;
