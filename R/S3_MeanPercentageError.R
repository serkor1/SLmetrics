# script: Mean Percentage Error
# date: 2024-10-10
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate Methods
# script start;

#' @title NULL
#' @usage NULL
#' @returns NULL
#' 
#' @templateVar .TITLE mean percentage error
#' @templateVar .FUN mpe
#' @templateVar .TASK regression
#' 
#' @template generic_description
#' @template regression_standard_template
#' 
#' @export
mpe <- function(...) {
  UseMethod(
    generic = "mpe"
  )
}

#' @usage NULL
#' 
#' @templateVar .TITLE mean percentage error
#' @templateVar .FUN mpe
#' @templateVar .TASK regression
#' 
#' @template generic_inherit
#' 
#' @export
weighted.mpe <- function(...) {
  UseMethod(
    generic = "weighted.mpe"
  )
}

# script end;
