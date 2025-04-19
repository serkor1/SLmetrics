# script: Relative Root Mean Squared Error
# date: 2024-12-27
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate Errors
# script start;

#' @title NULL
#' @usage NULL
#' @returns NULL
#' 
#' @templateVar .TITLE Relative Root Mean Squared Error
#' @templateVar .FUN rrmse
#' @templateVar .TASK regression
#' 
#' @template generic_description
#' @template regression_standard_template
#' 
#' @export
rrmse <- function(...) {
  UseMethod(
    generic = "rrmse"
  )
}

#' @usage NULL
#' 
#' @templateVar .TITLE concordance correlation coefficient
#' @templateVar .FUN rrmse
#' @templateVar .TASK regression
#' 
#' @template generic_inherit
#' 
#' @export
weighted.rrmse <- function(...) {
  UseMethod(
    generic = "weighted.rrmse"
  )
}

# script end;
