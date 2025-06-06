# script: Pinball Loss
# date: 2024-10-13
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate Methods
# script start;

#' @title NULL
#' @usage NULL
#' @returns NULL
#' 
#' @templateVar .TITLE pinball loss
#' @templateVar .FUN pinball
#' @templateVar .TASK regression
#' 
#' @template generic_description
#' @template regression_standard_template
#' 
#' @export
pinball <- function(...) {
  UseMethod(
    generic = "pinball"
  )
}

#' @usage NULL
#' 
#' @templateVar .TITLE pinball loss
#' @templateVar .FUN pinball
#' @templateVar .TASK regression
#' 
#' @template generic_inherit
#' 
#' @export
weighted.pinball <- function(...) {
  UseMethod(
    generic = "weighted.pinball"
  )
}

# script end;
