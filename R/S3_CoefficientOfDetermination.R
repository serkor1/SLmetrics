# script: Coefficient of Determination
# date: 2024-10-10
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate Methods
# script start;

#' @title NULL
#' @usage NULL
#' @returns NULL
#' 
#' @templateVar .TITLE \eqn{R^2}
#' @templateVar .FUN rsq
#' @templateVar .TASK regression
#' 
#' @template generic_description
#' @template regression_standard_template
#' 
#' @export
rsq <- function(...) {
  UseMethod(
    generic = "rsq"
  )
}

#' @usage NULL
#' 
#' @templateVar .TITLE \eqn{R^2}
#' @templateVar .FUN rsq
#' @templateVar .TASK regression
#' 
#' @template generic_inherit
#' 
#' @export
weighted.rsq <- function(...) {
  UseMethod(
    generic = "weighted.rsq"
  )
}

# script end;
