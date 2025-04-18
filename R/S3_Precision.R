# script: precision
# date: 2024-10-01
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate method
# script start;

#' @title NULL
#' @usage NULL
#' @returns NULL
#' 
#' @aliases ppv weighted.ppv
#' 
#' @section Other names:
#' 
#' The precision has other names depending on research field:
#' - Positive Predictive Value, [ppv()]
#' 
#' @templateVar .TITLE precision
#' @templateVar .FUN precision
#' @templateVar .TASK Classification
#' @templateVar .TASK Classification
#' @templateVar .MULTI_OUTPUT true
#' 
#' @template generic_description
#' @template classification_standard_template
#'
#' @export
precision <- function(...) {
  UseMethod(
    generic = "precision"
  )
}

#' @usage NULL
#' 
#' @templateVar .TITLE precision
#' @templateVar .FUN precision
#' @templateVar .TASK Classification
#' 
#' @template generic_inherit
#' 
#' @export
weighted.precision <- function(...) {
  UseMethod(
    generic = "weighted.precision"
  )
}

#' @export
ppv <- function(...) {
  UseMethod(
    generic = "ppv"
  )
}

#' @export
weighted.ppv <- function(...) {
  UseMethod(
    generic = "weighted.ppv"
  )
}

# script end;
