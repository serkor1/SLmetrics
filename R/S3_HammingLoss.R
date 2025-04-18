# script: Hamming Loss
# date: 2025-08-04
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate Methods
# script start;

#' @title NULL
#' @usage NULL
#' @returns NULL
#' 
#' @templateVar .TITLE hamming loss
#' @templateVar .FUN hammingloss
#' @templateVar .TASK Classification
#' @templateVar .MULTI_OUTPUT false
#' 
#' @template generic_description
#' @template classification_standard_template
#'
#' @export
hammingloss <- function(...) {
  UseMethod(
    generic = "hammingloss",
    object  = ..1
  )
}

#' @rdname classification_hammingloss
#' @usage
#' ## Generic S3 method
#' ## for weighted Hamming Loss
#' weighted.hammingloss(...)
#' @export
weighted.hammingloss <- function(...) {
  UseMethod(
    generic = "weighted.hammingloss",
    object  = ..1
  )
}

# script end;
