# script: Mean Absolute Percentage Error
# date: 2024-10-10
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate Methods
# script start;

#' @title NULL
#' @usage NULL
#' @returns NULL
#' 
#' @templateVar .TITLE mean absolute percentage error
#' @templateVar .FUN mape
#' @templateVar .TASK regression
#' 
#' @template generic_description
#' @template regression_standard_template
#' 
#' @export
mape <- function(...) {
  UseMethod(
    generic = "mape"
  )
}

#' @usage NULL
#' 
#' @templateVar .TITLE mean absolute percentage error
#' @templateVar .FUN mape
#' @templateVar .TASK regression
#' 
#' @template generic_inherit
#' 
#' @export
weighted.mape <- function(...) {
  UseMethod(
    generic = "weighted.mape"
  )
}

# script end;
