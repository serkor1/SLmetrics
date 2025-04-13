# script: recall
# date: 2024-09-29
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate method
# script start;

#' @title NULL
#' @usage NULL
#' @return NULL
#' 
#' @aliases sensitivity tpr weighted.sensitivity weighted.tpr
#' 
#' @section Other names:
#' 
#' The Recall has other names depending on research field:
#' - Sensitivity, [sensitivity()] 
#' - True Positive Rate, [tpr()]
#' 
#' @templateVar .TITLE recall
#' @templateVar .FUN recall
#' @templateVar .TASK Classification
#' @templateVar .MULTI_OUTPUT true
#' @template classification_standard_template
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
