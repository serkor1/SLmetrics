# script: Fowlkes-Mallows Index
# date: 2024-10-07
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate methods
# script start;

#' @templateVar .TITLE Fowlkes Mallows Index
#' @templateVar .FUN fmi
#' @templateVar .TASK Classification
#' @templateVar .SINGLE_OUTPUT TRUE
#' @template classification_inheritDotParams
#' @template classification_factor_example
#' @template classification_cmatrix_template
#' 
#' @usage
#' ## Generic S3 method
#' ## for unweighted Fowlkes
#' ## Mallows Index
#' fmi(...)
#' 
#' @family Classification
#' @family Unsupervised Learning
#' 
#' @export
fmi <- function(...) {
  UseMethod(
    generic = "fmi",
    object  = ..1
  )
}

#' @rdname fmi
#' @usage
#' ## Generic S3 method
#' ## for weighted Fowlkes
#' ## Mallows Index
#' weighted.fmi(...)
#' @export
weighted.fmi <- function(...) {
  UseMethod(
    generic = "weighted.fmi",
    object  = ..1
  )
}

# script end;
