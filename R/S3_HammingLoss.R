# script: Hamming Loss
# date: 2025-08-04
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate Methods
# script start;

#' @inherit accuracy
#' @templateVar .TITLE hamming loss
#' @templateVar .FUN hammingloss
#' @templateVar .TASK Classification
#' @templateVar .SINGLE_OUTPUT TRUE
#' @template classification_inheritDotParams
#' @template classification_factor_example
#' @template classification_cmatrix_template
#' 
#' @usage
#' ## Generic S3 method
#' ## for unweighted Hamming Loss
#' hammingloss(...)
#'
#' @family Classification
#' @family Supervised Learning
#'
#' @export
hammingloss <- function(...) {
  UseMethod(
    generic = "hammingloss",
    object  = ..1
  )
}

#' @rdname hammingloss
#' @usage
#' ## Generic S3 method
#' ## for weighted Hamming Loss
#' weighted.hammingloss(
#'  ...,
#'  w
#' )
#' @export
weighted.hammingloss <- function(...) {
  UseMethod(
    generic = "weighted.hammingloss",
    object  = ..1
  )
}

# script end;
