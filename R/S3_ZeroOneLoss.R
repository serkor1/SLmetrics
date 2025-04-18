# script: Zero-One Loss
# date: 2024-10-08
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate Methods
# script start;

#' @title NULL
#' @usage NULL
#' @returns NULL
#' 
#' @templateVar .TITLE Zero-One Loss
#' @templateVar .FUN zerooneloss
#' @templateVar .TASK Classification
#' @templateVar .MULTI_OUTPUT false
#' 
#' @template generic_description
#' @template classification_standard_template
#'
#' @export
zerooneloss <- function(...) {
  UseMethod(
    generic = "zerooneloss"
  )
}

#' @usage NULL
#' 
#' @templateVar .TITLE Zero-One Loss
#' @templateVar .FUN zerooneloss
#' @templateVar .TASK Classification
#' 
#' @template generic_inherit
#' 
#' @export
weighted.zerooneloss <- function(...) {
  UseMethod(
    generic = "weighted.zerooneloss"
  )
}

# script end;
