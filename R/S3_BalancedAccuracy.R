# script: Balanced Accuracy
# date: 2024-12-18
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate methods for balanced accuracy
# script start;

#' @title NULL
#' @usage NULL
#' @returns NULL
#' 
#' @templateVar .TITLE balanced accuracy
#' @templateVar .FUN baccuracy
#' @templateVar .TASK Classification
#' @templateVar .MULTI_OUTPUT false
#' 
#' @template generic_description
#' @template classification_standard_template
#'
#' @export
baccuracy <- function(...) {
  UseMethod(
    generic = "baccuracy"
  )
}

#' @usage NULL
#' 
#' @templateVar .TITLE balanced accuracy
#' @templateVar .FUN baccuracy
#' @templateVar .TASK Classification
#' 
#' @template generic_inherit
#' 
#' @export
weighted.baccuracy <- function(...) {
  UseMethod(
    generic = "weighted.baccuracy"
  )
}

# script end;
