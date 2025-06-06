# script: Geometric Mean Squared Error
# date: 2024-04-29
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate Errors
# script start;

#' @title NULL
#' @usage NULL
#' @returns NULL
#' 
#' @templateVar .TITLE geometric mean squared error
#' @templateVar .FUN gmse
#' @templateVar .TASK regression
#' 
#' @template generic_description
#' @template regression_standard_template
#' 
#' @export
gmse <- function(...) {
  UseMethod(
    generic = "gmse"
  )
}

#' @usage NULL
#' 
#' @templateVar .TITLE geometric mean squared error
#' @templateVar .FUN gmse
#' @templateVar .TASK regression
#' 
#' @template generic_inherit
#' 
#' @export
weighted.gmse <- function(...) {
  UseMethod(
    generic = "weighted.gmse"
  )
}

# script end;
