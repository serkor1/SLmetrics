# script: recall
# date: 2024-09-29
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate method
# script start;

#' @aliases sensitivity tpr weighted.sensitivity weighted.tpr
#' 
#' @templateVar .TITLE recall
#' @templateVar .FUN recall
#' @templateVar .TASK Classification
#' @template classification_inheritDotParams
#' @template classification_factor_example
#' @template classification_cmatrix_template
#' 
#' @section Other names:
#' 
#' The Recall has other names depending on research field:
#' - Sensitivity, [sensitivity()] 
#' - True Positive Rate, [tpr()]
#' 
#' @usage
#' ## Generic S3 method
#' ## for unweighted recall
#' recall(...)
#'
#' @family Classification
#' @family Supervised Learning
#' 
#' @export
recall <- function(...) {
  UseMethod(
    generic = "recall",
    object  = ..1
  )
}

#' @rdname recall
#' @usage
#' ## Generic S3 method
#' ## for weighted recall
#' weighted.recall(...)
#' @export
weighted.recall <- function(...) {
  UseMethod(
    generic = "weighted.recall",
    object  = ..1
  )
}

#' @export
sensitivity <- function(...) {
  UseMethod(
    generic = "sensitivity",
    object  = ..1
  )
}

#' @export
weighted.sensitivity <- function(...) {
  UseMethod(
    generic = "weighted.sensitivity",
    object  = ..1
  )
}

#' @export
tpr <- function(...) {
  UseMethod(
    generic = "tpr",
    object  = ..1
  )
}

#' @export
weighted.tpr <- function(...) {
  UseMethod(
    generic = "weighted.tpr",
    object  = ..1
  )
}

# script end;
