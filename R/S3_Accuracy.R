# script: Accuracy
# date: 2024-10-05
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate methods for accuracy
# script start;

#' @title NULL
#' @usage NULL
#' @returns NULL
#' 
#' @templateVar .TITLE accuracy
#' @templateVar .FUN accuracy
#' @templateVar .TASK Classification
#' @templateVar .MULTI_OUTPUT false
#' 
#' @template generic_description
#' @template classification_standard_template
#'
#' @export
accuracy <- function(...) {
  UseMethod(
    generic = "accuracy"
  )
}

#' @usage NULL
#' 
#' @templateVar .TITLE accuracy
#' @templateVar .FUN accuracy
#' @templateVar .TASK Classification
#' 
#' @template generic_inherit
#' 
#' @export
weighted.accuracy <- function(...) {
  UseMethod(
    generic = "weighted.accuracy"
  )
}

# script end;
