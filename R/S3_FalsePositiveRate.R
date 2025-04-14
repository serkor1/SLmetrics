# script: False Positive Rate
# date: 2024-10-07
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate Methods
# for False Positive Rate
# script start;

#' @title NULL
#' @usage NULL
#' @returns NULL
#' 
#' @aliases fallout weighted.fallout
#' 
#' @templateVar .TITLE false positive rate
#' @templateVar .FUN fpr
#' @templateVar .TASK Classification
#' @templateVar .MULTI_OUTPUT true
#' @template classification_standard_template
#'
#' @export
fpr <- function(...) {
  UseMethod(
    generic = "fpr"
  )
}

#' @rdname fpr
#' @usage
#' ## Generic S3 method
#' ## for weighted False Positive
#' ## Rate
#' weighted.fpr(...)
#' @export
weighted.fpr <- function(...) {
  UseMethod(
    generic = "weighted.fpr"
  )
}

#' @export
fallout <- function(...) {
  UseMethod(
    generic = "fallout"
  )
}

#' @export
weighted.fallout <- function(...) {
  UseMethod(
    generic = "weighted.fallout"
  )
}

# script end;
