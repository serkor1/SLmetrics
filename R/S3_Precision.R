# script: precision
# date: 2024-10-01
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate method
# script start;

#' @title NULL
#' @usage NULL
#' @returns NULL
#' 
#' @aliases ppv weighted.ppv
#' 
#' @section Other names:
#' 
#' The precision has other names depending on research field:
#' - Positive Predictive Value, [ppv()]
#' 
#' @templateVar .TITLE precision
#' @templateVar .FUN precision
#' @templateVar .TASK Classification
#' @templateVar .TASK Classification
#' @templateVar .MULTI_OUTPUT true
#' @template classification_standard_template
#' 
#' @export
precision <- function(...) {
  UseMethod(
    generic = "precision",
    object  = ..1
  )
}

#' @rdname precision
#' @usage
#' ## Generic S3 method
#' ## for weighted precision
#' weighted.precision(...)
#' @export
weighted.precision <- function(...) {
  UseMethod(
    generic = "weighted.precision",
    object  = ..1
  )
}

#' @export
ppv <- function(...) {
  UseMethod(
    generic = "ppv",
    object  = ..1
  )
}

#' @export
weighted.ppv <- function(...) {
  UseMethod(
    generic = "weighted.ppv",
    object  = ..1
  )
}

# script end;
