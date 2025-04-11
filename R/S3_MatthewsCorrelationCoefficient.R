# script: Matthews Correlation Coefficient
# date: 2024-10-06
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate MCC methods
# script start;

#' @aliases phi weighted.phi
#' 
#' @templateVar .TITLE Matthews Correlation Coefficient
#' @templateVar .FUN mcc
#' @templateVar .TASK Classification
#' @templateVar .SINGLE_OUTPUT TRUE
#' @template classification_inheritDotParams
#' @template classification_factor_example
#' @template classification_cmatrix_template
#'
#' @section Other names:
#' 
#' The Matthews Correlation Coefficient has other names depending on research field:
#' - \eqn{\phi}-coefficient, [phi()]
#' 
#' @usage
#' ## Generic S3 method
#' ## for unweighted Matthews
#' ## Correlation Coefficient
#' mcc(...)
#'
#' @family Classification
#' @family Supervised Learning
#'
#' @export
mcc <- function(...) {
  UseMethod(
    generic = "mcc",
    object = ..1
  )
}

#' @rdname mcc
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
