# script: Root Mean Squared Error
# date: 2024-10-09
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate Errors
# script start;

#' @title NULL
#' @usage NULL
#' @returns NULL
#' 
#' @templateVar .TITLE root mean squared error
#' @templateVar .FUN rmse
#' @templateVar .TASK regression
#' 
#' @template generic_description
#' @template regression_standard_template
#' 
#' @export
rmse <- function(...) {
  UseMethod(
    generic = "rmse"
  )
}

#' @usage NULL
#' 
#' @templateVar .TITLE root mean squared error
#' @templateVar .FUN rmse
#' @templateVar .TASK regression
#' 
#' @template generic_inherit
#' 
#' @export
weighted.rmse <- function(...) {
  UseMethod(
    generic = "weighted.rmse"
  )
}

# script end;
