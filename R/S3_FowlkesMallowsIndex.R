# script: Fowlkes-Mallows Index
# date: 2024-10-07
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate methods
# script start;

#' @title NULL
#' @usage NULL
#' @returns NULL
#' 
#' @templateVar .TITLE Fowlkes Mallows Index
#' @templateVar .FUN fmi
#' @templateVar .TASK Classification
#' @templateVar .MULTI_OUTPUT false
#' 
#' @template generic_description
#' @template classification_standard_template
#'
#' @export
fmi <- function(...) {
  UseMethod(
    generic = "fmi"
  )
}

#' @usage NULL
#' 
#' @templateVar .TITLE Fowlkes Mallows Index
#' @templateVar .FUN fmi
#' @templateVar .TASK Classification
#' 
#' @template generic_inherit
#' 
#' @export
weighted.fmi <- function(...) {
  UseMethod(
    generic = "weighted.fmi"
  )
}

# script end;
