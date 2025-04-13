# script: Negative Predictive Value
# date: 2024-10-07
# author: Serkan Korkmaz, serkor1@duck.com
# objective:
# script start;

#' @title NULL
#' @usage NULL
#' @return NULL
#' 
#' @templateVar .TITLE Negative Predictive Value
#' @templateVar .FUN npv
#' @templateVar .TASK Classification
#' @templateVar .MULTI_OUTPUT true
#' @template classification_standard_template
#' 
#' @export
npv <- function(...) {
  UseMethod(
    generic = "npv",
    object  = ..1
  )
}

#' @rdname npv
#' @usage 
#' ## Generic S3 method
#' ## for weighted Negative
#' ## Predictive Value
#' npv(...)
#' @export
weighted.npv <- function(...) {
  UseMethod(
    generic = "weighted.npv",
    object  = ..1
  )
}

# script end;
