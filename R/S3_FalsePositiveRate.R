# script: False Positive Rate
# date: 2024-10-07
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate Methods
# for False Positive Rate
# script start;

#' @aliases fallout weighted.fallout
#' @templateVar .TITLE False Positive Rate
#' @templateVar .FUN fpr
#' @templateVar .TASK Classification
#' @template classification_inheritDotParams
#' @template classification_factor_example
#' @template classification_cmatrix_template
#' 
#' @usage 
#' ## Generic S3 method
#' ## for unweighted False
#' ## Positive Rate
#' fpr(...)
#' 
#' @family Classification
#' @family Supervised Learning
#'
#' @export
fpr <- function(...) {
  UseMethod(
    generic = "fpr",
    object  = ..1
  )
}

#' @rdname fpr
#' @usage
#' ## Generic S3 method
#' ## for weighted false positive
#' ## rate
#' weighted.fpr(...)
#' @export
weighted.fpr <- function(...) {
  UseMethod(
    generic = "weighted.fpr",
    object  = ..1
  )
}

#' @export
fallout <- function(...) {
  UseMethod(
    generic = "fallout",
    object  = ..1
  )
}

#' @export
weighted.fallout <- function(...) {
  UseMethod(
    generic = "weighted.fallout",
    object  = ..1
  )
}

# script end;
