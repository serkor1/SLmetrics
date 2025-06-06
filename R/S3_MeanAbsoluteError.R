# script: Mean Absolute Error
# date: 2024-10-10
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate Methods
# script start;

#' @title NULL
#' @usage NULL
#' @returns NULL
#' 
#' @templateVar .TITLE mean absolute error
#' @templateVar .FUN mae
#' @templateVar .TASK regression
#' 
#' @template generic_description
#' @template regression_standard_template
#' 
#' @export
mae <- function(...) {
  UseMethod(
    generic = "mae"
  )
}

#' @usage NULL
#' 
#' @templateVar .TITLE mean absolute error
#' @templateVar .FUN mae
#' @templateVar .TASK regression
#' 
#' @template generic_inherit
#' 
#' @export
weighted.mae <- function(...) {
  UseMethod(
    generic = "weighted.mae"
  )
}

# script end;
