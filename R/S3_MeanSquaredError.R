# script: Mean Squared Error
# date: 2024-10-09
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate Errors
# script start;

#' @title NULL
#' @usage NULL
#' @returns NULL
#' 
#' @templateVar .TITLE mean squared error
#' @templateVar .FUN mse
#' @templateVar .TASK regression
#' 
#' @template generic_description
#' @template regression_standard_template
#' 
#' @export
mse <- function(...) {
  UseMethod(
    generic = "mse"
  )
}

#' @usage NULL
#' 
#' @templateVar .TITLE mean squared error
#' @templateVar .FUN mse
#' @templateVar .TASK regression
#' 
#' @template generic_inherit
#' 
#' @export
weighted.mse <- function(...) {
  UseMethod(
    generic = "weighted.mse"
  )
}

# script end;
