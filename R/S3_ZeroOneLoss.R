# script: Zero-One Loss
# date: 2024-10-08
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate Methods
# script start;

#' @templateVar .TITLE Zero-One Loss
#' @templateVar .FUN zerooneloss
#' @templateVar .TASK Classification
#' @templateVar .SINGLE_OUTPUT TRUE
#' @template classification_inheritDotParams
#' @template classification_factor_example
#' @template classification_cmatrix_template
#' 
#' @usage
#' ## Generic S3 method
#' zerooneloss(...)
#' 
#' @family Classification
#' @family Supervised Learning
#'
#' @export
zerooneloss <- function(...) {
  UseMethod(
    generic = "zerooneloss",
    object  = ..1
  )
}

#' @rdname zerooneloss
#' @usage
#' ## Generic S3 method
#' weighted.zerooneloss(..)
#' @export
weighted.zerooneloss <- function(...) {
  UseMethod(
    generic = "weighted.zerooneloss",
    object  = ..1
  )
}

# script end;
