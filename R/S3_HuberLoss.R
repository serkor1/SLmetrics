# script: Huber Loss
# date: 2024-10-09
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate Methods
# script start;

#' @title NULL
#' @usage NULL
#' @returns NULL
#' 
#' @templateVar .TITLE Huber Loss
#' @templateVar .FUN huberloss
#' @templateVar .TASK regression
#' 
#' @template generic_description
#' @template regression_standard_template
#' 
#' @export
huberloss <- function(...) {
  UseMethod(
    generic = "huberloss"
  )
}

#' @usage NULL
#' 
#' @templateVar .TITLE Huber Loss
#' @templateVar .FUN huberloss
#' @templateVar .TASK regression
#' 
#' @template generic_inherit
#' 
#' @export
weighted.huberloss <- function(...) {
  UseMethod(
    generic = "weighted.huberloss"
  )
}

# script end;
