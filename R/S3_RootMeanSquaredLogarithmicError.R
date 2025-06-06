# script: Root Mean Squared Logarithmic Error
# date: 2024-10-09
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate Methods
# script start;

#' @title NULL
#' @usage NULL
#' @returns NULL
#' 
#' @templateVar .TITLE Root Mean Squared Logarithmic Error
#' @templateVar .FUN rmsle
#' @templateVar .TASK regression
#' 
#' @template generic_description
#' @template regression_standard_template
#' 
#' @export
rmsle <- function(...) {
  UseMethod(
    generic = "rmsle"
  )
}

#' @usage NULL
#' 
#' @templateVar .TITLE Root Mean Squared Logarithmic Error
#' @templateVar .FUN rmsle
#' @templateVar .TASK regression
#' 
#' @template generic_inherit
#' 
#' @export
weighted.rmsle <- function(...) {
  UseMethod(
    generic = "weighted.rmsle"
  )
}

# script end;
