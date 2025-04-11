# script: False Discovery Rate
# date: 2024-10-07
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate Methods
# script start;

#' @templateVar .TITLE false discovery rate
#' @templateVar .FUN fdr
#' @templateVar .TASK Classification
#' @template classification_inheritDotParams
#' @template classification_factor_example
#' @template classification_cmatrix_template
#' 
#' @usage 
#' ## Generic S3 method for
#' ## unweighted False Discovery
#' ## Rate
#' fdr(...)
#' 
#' @family Classification
#' @family Supervised Learning
#' 
#' @export
fdr <- function(...) {
  UseMethod(
    generic = "fdr",
    object   = ..1
  )
}

#' @rdname fdr
#' @usage 
#' ## Generic S3 method for
#' ## weighted False Discovery
#' ## Rate
#' weighted.fdr(...)
#' @export
weighted.fdr <- function(...) {
  UseMethod(
    generic = "weighted.fdr",
    object   = ..1
  )
}

# script end;
