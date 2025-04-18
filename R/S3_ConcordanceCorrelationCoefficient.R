# script: Concordance Correlation Coefficient
# date: 2024-10-10
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate Methods
# script start;

#' @title NULL
#' @usage NULL
#' @returns NULL
#' 
#' @templateVar .TITLE concordance correlation coefficient
#' @templateVar .FUN ccc
#' @templateVar .TASK regression
#' 
#' @template generic_description
#' @template regression_standard_template
#' 
#' @export
ccc <- function(...) {
  UseMethod(
    generic = "ccc"
  )
}

#' @usage NULL
#' 
#' @templateVar .TITLE concordance correlation coefficient
#' @templateVar .FUN ccc
#' @templateVar .TASK regression
#' 
#' @template generic_inherit
#' 
#' @export
weighted.ccc <- function(...) {
  UseMethod(
    generic = "weighted.ccc"
  )
}

# script end;
