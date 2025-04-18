# script: specificity
# author: Serkan Korkmaz, serkor1@duck.com
# date: 2024-10-02
# objective: Generate method
# script start;

#' @title NULL
#' @usage NULL
#' @returns NULL
#' 
#' @aliases tnr selectivity weighted.tnr weighted.selectivity
#' 
#' @section Other names:
#' 
#' The specificity has other names depending on research field:
#' - True Negative Rate, [tnr()] 
#' - Selectivity, [selectivity()]
#' 
#' 
#' @templateVar .TITLE specificity
#' @templateVar .FUN specificity
#' @templateVar .TASK Classification
#' @templateVar .MULTI_OUTPUT true
#' 
#' @template generic_description
#' @template classification_standard_template
#'
#' @export
specificity <- function(...) {
  UseMethod(
    generic = "specificity"
  )
}

#' @usage NULL
#' 
#' @templateVar .TITLE specificity
#' @templateVar .FUN specificity
#' @templateVar .TASK Classification
#' 
#' @template generic_inherit
#' 
#' @export
weighted.specificity <- function(...) {
    UseMethod(
      generic = "weighted.specificity"
    )
}

#' @export
tnr <- function(...) {
  UseMethod(
    generic = "tnr"
  )
}

#' @export
weighted.tnr <- function(...) {
    UseMethod(
      generic = "weighted.tnr"
    )
}

#' @export
selectivity <- function(...) {
  UseMethod(
    generic = "selectivity"
  )
}

#' @export
weighted.selectivity <- function(...) {
  UseMethod(
    generic = "weighted.selectivity"
  )
}

# script end;
