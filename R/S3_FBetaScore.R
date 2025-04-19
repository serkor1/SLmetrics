# script: fbetascore
# date: 2024-10-01
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate methods
# script start; 

#' @title NULL
#' @usage NULL
#' @returns NULL
#' 
#' @templateVar .TITLE \eqn{F_{\beta}}
#' @templateVar .FUN fbeta
#' @templateVar .TASK Classification
#' @templateVar .MULTI_OUTPUT true
#' 
#' @template generic_description
#' @template classification_standard_template
#'
#' @export
fbeta <- function(...) {
  UseMethod(
    generic = "fbeta"
  )
}

#' @usage NULL
#' 
#' @templateVar .TITLE \eqn{F_{\beta}}
#' @templateVar .FUN fbeta
#' @templateVar .TASK Classification
#' 
#' @template generic_inherit
#' 
#' @export
weighted.fbeta <- function(...) {
  UseMethod(
    generic = "weighted.fbeta"
  )
}

# script end;
