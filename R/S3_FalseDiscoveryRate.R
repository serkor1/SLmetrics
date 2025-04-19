# script: False Discovery Rate
# date: 2024-10-07
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate Methods
# script start;

#' @title NULL
#' @usage NULL
#' @returns NULL
#' 
#' @templateVar .TITLE false discovery rate
#' @templateVar .FUN fdr
#' @templateVar .TASK Classification
#' @templateVar .MULTI_OUTPUT true
#' 
#' @template generic_description
#' @template classification_standard_template
#'
#' @export
fdr <- function(...) {
  UseMethod(
    generic = "fdr"
  )
}

#' @usage NULL
#' 
#' @templateVar .TITLE false discovery rate
#' @templateVar .FUN fdr
#' @templateVar .TASK Classification
#' 
#' @template generic_inherit
#' 
#' @export
weighted.fdr <- function(...) {
  UseMethod(
    generic = "weighted.fdr"
  )
}

# script end;
