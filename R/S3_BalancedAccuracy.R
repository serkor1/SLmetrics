# script: Balanced Accuracy
# date: 2024-12-18
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate methods for balanced accuracy
# script start;

#' @templateVar .TITLE balanced accuracy
#' @templateVar .FUN baccuracy
#' @templateVar .TASK Classification
#' @templateVar .SINGLE_OUTPUT TRUE
#' @template classification_inheritDotParams
#' @template classification_factor_example
#' @template classification_cmatrix_template
#' 
#' @usage
#' ## Generic S3 method
#' ## for unweighted balanced
#' ## accuracy
#' baccuracy(...)
#' 
#' @returns
#'
#' A [numeric]-vector of [length] 1
#'
#'
#' @family Classification
#' @family Supervised Learning
#'
#' @export
baccuracy <- function(...) {
  UseMethod(
    generic = "baccuracy",
    object  = ..1
  )
}

#' @rdname baccuracy
#' @usage
#' ## Generic S3 method
#' ## for weighted balanced
#' ## accuracy
#' weighted.baccuracy(...)
#' @export
weighted.baccuracy <- function(...) {
  UseMethod(
    generic = "weighted.baccuracy",
    object  = ..1
  )
}

# script end;
