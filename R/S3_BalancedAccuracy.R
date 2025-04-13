# script: Balanced Accuracy
# date: 2024-12-18
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate methods for balanced accuracy
# script start;

#' @title NULL
#' @usage NULL
#' @return NULL
#' 
#' @templateVar .TITLE balanced accuracy
#' @templateVar .FUN baccuracy
#' @templateVar .TASK Classification
#' @templateVar .MULTI_OUTPUT false
#' @template classification_standard_template
#'
#' @export
baccuracy <- function(...) {
  UseMethod(
    generic = "baccuracy"
  )
}

#' @rdname baccuracy
#' @usage
#' ## Generic S3 method
#' ## for weighted Balanced
#' ## Accuracy
#' weighted.baccuracy(...)
#' @export
weighted.baccuracy <- function(...) {
  UseMethod(
    generic = "weighted.baccuracy"
  )
}

# script end;
