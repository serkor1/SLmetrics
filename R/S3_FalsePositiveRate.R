# script: False Positive Rate
# date: 2024-10-07
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate Methods
# for False Positive Rate
# script start;

#' @title NULL
#' @usage NULL
#' @returns NULL
#' 
#' @aliases fallout weighted.fallout
#' 
#' @section Other names:
#' 
#' The false positive rate has other names depending on research field:
#' - Fallout, [fallout()]
#' 
#' @templateVar .TITLE false positive rate
#' @templateVar .FUN fpr
#' @templateVar .TASK Classification
#' @templateVar .MULTI_OUTPUT true
#' 
#' @template generic_description
#' @template classification_standard_template
#'
#' @export
fpr <- function(...) {
  UseMethod(
    generic = "fpr"
  )
}

#' @usage NULL
#' 
#' @templateVar .TITLE false positive rate
#' @templateVar .FUN fpr
#' @templateVar .TASK Classification
#' 
#' @template generic_inherit
#' 
#' @export
weighted.fpr <- function(...) {
  UseMethod(
    generic = "weighted.fpr"
  )
}

#' @export
fallout <- function(...) {
  UseMethod(
    generic = "fallout"
  )
}

#' @export
weighted.fallout <- function(...) {
  UseMethod(
    generic = "weighted.fallout"
  )
}

# script end;
