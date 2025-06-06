# script:Symmetric Mean Absolute Error
# date: 2024-10-10
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate Methods
# script start;

#' @title NULL
#' @usage NULL
#' @returns NULL
#' 
#' @templateVar .TITLE Symmetric Mean Absolutte Percentage Error
#' @templateVar .FUN smape
#' @templateVar .TASK regression
#' 
#' @template generic_description
#' @template regression_standard_template
#' 
#' @export
smape <- function(...) {
  UseMethod(
    generic = "smape"
  )
}

#' @usage NULL
#' 
#' @templateVar .TITLE Symmetric Mean Absolutte Percentage Error
#' @templateVar .FUN smape
#' @templateVar .TASK regression
#' 
#' @template generic_inherit
#' 
#' @export
weighted.smape <- function(...) {
  UseMethod(
    generic = "weighted.smape"
  )
}


# script end;
