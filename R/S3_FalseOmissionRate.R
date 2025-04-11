# script: False Omission Rate
# date: 2024-10-07
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate Method
# script start;

#' @inherit specificity
#' 
#' @templateVar .TITLE false omission rate
#' @templateVar .FUN fer
#' @templateVar .TASK Classification
#' @template classification_inheritDotParams
#' @template classification_factor_example
#' @template classification_cmatrix_template
#' 
#' @usage 
#' ## Generic S3 method
#' ## for unweighted False
#' ## Omission Rate
#' fer(...)
#' 
#' @family Classification
#' @family Supervised Learning
#' 
#' @export
fer <- function(...) {
  UseMethod(
    generic = "fer",
    object  = ..1
  )
}

#' @rdname fer
#' @usage 
#' ## Generic S3 method
#' ## for weighted False
#' ## Omission Rate
#' weighted.fer(...)
#' @export
weighted.fer <- function(...) {
  UseMethod(
    generic = "weighted.fer",
    object  = ..1
  )
}

# script end;
