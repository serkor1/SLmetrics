# script: precision
# date: 2024-10-01
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate method
# script start;

#' @aliases ppv weighted.ppv
#' 
#' @templateVar .TITLE precision
#' @templateVar .FUN precision
#' @templateVar .TASK Classification
#' @template classification_inheritDotParams
#' @template classification_factor_example
#' @template classification_cmatrix_template
#' 
#' @section Other names:
#' 
#' The precision has other names depending on research field:
#' - Positive Predictive Value, [ppv()]
#' 
#' @usage
#' ## Generic S3 method
#' ## for unweighted precision
#' precision(...)
#'
#' @family Classification
#' @family Supervised Learning
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
