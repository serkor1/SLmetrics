# script: Matthews Correlation Coefficient
# date: 2024-10-06
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate MCC methods
# script start;

#' @title NULL
#' @usage NULL
#' @returns NULL
#' 
#' @aliases phi weighted.phi
#' 
#' @templateVar .TITLE Matthews Correlation Coefficient
#' @templateVar .FUN mcc
#' @templateVar .TASK Classification
#' @templateVar .MULTI_OUTPUT false
#' 
#' @template generic_description
#' @template classification_standard_template
#'
#' @section Other names:
#' 
#' The Matthews Correlation Coefficient has other names depending on research field:
#' - \eqn{\phi}-coefficient, [phi()]
#'
#' @export
mcc <- function(...) {
  UseMethod(
    generic = "mcc"
  )
}

#' @usage NULL
#' 
#' @templateVar .TITLE Matthews Correlation Coefficient
#' @templateVar .FUN mcc
#' @templateVar .TASK Classification
#' 
#' @template generic_inherit
#' 
#' @export
weighted.mcc <- function(...) {
  UseMethod(
    generic = "weighted.mcc"
  )
}

#' @export
phi <- function(...) {
  UseMethod(
    generic = "phi"
  )
}

#' @export
weighted.phi <- function(...) {
  UseMethod(
    generic = "weighted.phi"
  )
}

# script end;
