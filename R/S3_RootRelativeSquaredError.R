# script: Root Relative Squared Error
# date: 2024-10-11
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Genereate Methods
# script start;

#' @title NULL
#' @usage NULL
#' @returns NULL
#' 
#' @templateVar .TITLE Root Relative Squared Error
#' @templateVar .FUN rrse
#' @templateVar .TASK regression
#' 
#' @template generic_description
#' @template regression_standard_template
#' 
#' @export
rrse <- function(...) {
  UseMethod(
    generic = "rrse"
  )
}

#' @usage NULL
#' 
#' @templateVar .TITLE Root Relative Squared Error
#' @templateVar .FUN rrse
#' @templateVar .TASK regression
#' 
#' @template generic_inherit
#' 
#' @export
weighted.rrse <- function(...) {
  UseMethod(
    generic = "weighted.rrse"
  )
}

# script end;
