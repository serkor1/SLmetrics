# script: Relative Absolute Error
# date: 2024-10-11
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate Methods
# script start;

#' @title NULL
#' @usage NULL
#' @returns NULL
#' 
#' @templateVar .TITLE Relative Absolute Error
#' @templateVar .FUN rae
#' @templateVar .TASK regression
#' 
#' @template generic_description
#' @template regression_standard_template
#' 
#' @export
rae <- function(...) {
  UseMethod(
    generic = "rae"
  )
}

#' @usage NULL
#' 
#' @templateVar .TITLE Relative Absolute Error
#' @templateVar .FUN rae
#' @templateVar .TASK regression
#' 
#' @template generic_inherit
#' 
#' @export
weighted.rae <- function(...) {
  UseMethod(
    generic = "weighted.rae"
  )
}

# script end;
