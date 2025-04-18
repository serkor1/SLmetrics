# script: Brier Score
# date: 2025-04-16
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate methods for Brier Score
# script start;

#' @title NULL
#' @usage NULL
#' @returns NULL
#' 
#' @templateVar .TITLE Brier Score
#' @templateVar .FUN brier.score
#' @templateVar .TASK Classification
#' 
#' @template generic_description
#' @template classification_proper_template
#'
#' @export
brier.score <- function(...) {
  UseMethod(
    generic = "brier.score"
  )
}

#' @usage NULL
#' 
#' @templateVar .TITLE Brier Score
#' @templateVar .FUN brier.score
#' @templateVar .TASK Classification
#' 
#' @template generic_inherit
#' 
#' @export
weighted.brier.score <- function(...) {
  UseMethod(
    generic = "weighted.brier.score"
  )
}

# script end;
