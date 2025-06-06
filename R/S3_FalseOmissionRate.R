# script: False Omission Rate
# date: 2024-10-07
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate Method
# script start;

#' @title NULL
#' @usage NULL
#' @returns NULL
#' 
#' @templateVar .TITLE false omission rate
#' @templateVar .FUN fer
#' @templateVar .TASK Classification
#' @templateVar .MULTI_OUTPUT true
#' 
#' @template generic_description
#' @template classification_standard_template
#'
#' @export
fer <- function(...) {
  UseMethod(
    generic = "fer"
  )
}

#' @usage NULL
#' 
#' @templateVar .TITLE false omission rate
#' @templateVar .FUN fer
#' @templateVar .TASK Classification
#' 
#' @template generic_inherit
#' 
#' @export
weighted.fer <- function(...) {
  UseMethod(
    generic = "weighted.fer"
  )
}

# script end;
