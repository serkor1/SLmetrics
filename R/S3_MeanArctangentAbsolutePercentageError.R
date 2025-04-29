# script: Mean Arctangent Absolute Percentage Error
# date: 2024-04-28
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate Methods
# script start;

#' @title NULL
#' @usage NULL
#' @returns NULL
#' 
#' @templateVar .TITLE mean arctangent absolute percentage error
#' @templateVar .FUN maape
#' @templateVar .TASK regression
#' 
#' @template generic_description
#' @template regression_standard_template
#' 
#' @export
maape <- function(...) {
  UseMethod(
    generic = "maape"
  )
}

#' @usage NULL
#' 
#' @templateVar .TITLE mean arctangent absolute percentage error
#' @templateVar .FUN maape
#' @templateVar .TASK regression
#' 
#' @template generic_inherit
#' 
#' @export
weighted.maape <- function(...) {
  UseMethod(
    generic = "weighted.maape"
  )
}

# script end;
