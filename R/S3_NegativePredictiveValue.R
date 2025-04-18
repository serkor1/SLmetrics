# script: Negative Predictive Value
# date: 2024-10-07
# author: Serkan Korkmaz, serkor1@duck.com
# objective:
# script start;

#' @title NULL
#' @usage NULL
#' @returns NULL
#' 
#' @templateVar .TITLE Negative Predictive Value
#' @templateVar .FUN npv
#' @templateVar .TASK Classification
#' @templateVar .MULTI_OUTPUT true
#' 
#' @template generic_description
#' @template classification_standard_template
#'
#' @export
npv <- function(...) {
  UseMethod(
    generic = "npv"
  )
}

#' @usage NULL
#' 
#' @templateVar .TITLE Negative Predictive Value
#' @templateVar .FUN npv
#' @templateVar .TASK Classification
#' 
#' @template generic_inherit
#' 
#' @export
weighted.npv <- function(...) {
  UseMethod(
    generic = "weighted.npv"
  )
}

# script end;
