# script: specificity
# author: Serkan Korkmaz, serkor1@duck.com
# date: 2025-19-01
# objective: Generate method
# script start;

#' @title NULL
#' @usage NULL
#' @returns NULL
#' 
#' @templateVar .TITLE Logarithmic Loss
#' @templateVar .FUN logloss
#' @templateVar .TASK Classification
#' 
#' @template generic_description
#' @template classification_entropy_template
#' 
#' @export
logloss <- function(...) {
  UseMethod(
    generic = "logloss"
  )
}

#' @usage NULL
#' 
#' @templateVar .TITLE Logarithmic Loss
#' @templateVar .FUN logloss
#' @templateVar .TASK Classification
#' 
#' @template generic_inherit
#' 
#' @export
weighted.logloss <- function(...) {
  UseMethod(
    generic = "weighted.logloss"
  )
}

# script end;
