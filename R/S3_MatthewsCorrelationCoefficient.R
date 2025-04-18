# script: Matthews Correlation Coefficient
# date: 2024-10-06
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate MCC methods
# script start;

#' @title NULL
#' @usage NULL
#' @returns NULL
#' 
#' @aliases phi weighted.phi
#' 
#' @templateVar .TITLE Matthews Correlation Coefficient
#' @templateVar .FUN mcc
#' @templateVar .TASK Classification
#' @templateVar .MULTI_OUTPUT false
#' 
#' @template generic_description
#' @template classification_standard_template
#'
#' @section Other names:
#' 
#' The Matthews Correlation Coefficient has other names depending on research field:
#' - \eqn{\phi}-coefficient, [phi()]
#'
#' @export
mcc <- function(...) {
  UseMethod(
    generic = "mcc",
    object = ..1
  )
}

#' @rdname classification_mcc
#' @usage
#' ## Generic S3 method
#' ## for weighted Matthews
#' ## Correlation Coefficient
#' weighted.mcc(...)
#' @export
weighted.mcc <- function(...) {
  UseMethod(
    generic = "weighted.mcc",
    object = ..1
  )
}

#' @export
phi <- function(...) {
  UseMethod(
    generic = "phi",
    object = ..1
  )
}

#' @export
weighted.phi <- function(...) {
  UseMethod(
    generic = "weighted.phi",
    object = ..1
  )
}

# script end;
