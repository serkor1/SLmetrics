# script: recall
# date: 2024-09-29
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate method
# script start;

#' @title NULL
#' @usage NULL
#' @returns NULL
#' 
#' @aliases sensitivity tpr weighted.sensitivity weighted.tpr
#' 
#' @section Other names:
#' 
#' The Recall has other names depending on research field:
#' - Sensitivity, [sensitivity()] 
#' - True Positive Rate, [tpr()]
#' 
#' @templateVar .TITLE recall
#' @templateVar .FUN recall
#' @templateVar .TASK Classification
#' @templateVar .MULTI_OUTPUT true
#' 
#' @template generic_description
#' @template classification_standard_template
#'
#' @export
recall <- function(...) {
  UseMethod(
    generic = "recall"
  )
}

#' @usage NULL
#' 
#' @templateVar .TITLE recall
#' @templateVar .FUN recall
#' @templateVar .TASK Classification
#' 
#' @template generic_inherit
#' 
#' @export
weighted.recall <- function(...) {
  UseMethod(
    generic = "weighted.recall"
  )
}

#' @export
sensitivity <- function(...) {
  UseMethod(
    generic = "sensitivity"
  )
}

#' @export
weighted.sensitivity <- function(...) {
  UseMethod(
    generic = "weighted.sensitivity"
  )
}

#' @export
tpr <- function(...) {
  UseMethod(
    generic = "tpr"
  )
}

#' @export
weighted.tpr <- function(...) {
  UseMethod(
    generic = "weighted.tpr"
  )
}

# script end;
