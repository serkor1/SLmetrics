# script: specificity
# author: Serkan Korkmaz, serkor1@duck.com
# date: 2025-19-01
# objective: Generate method
# script start;

#' @title NULL
#' @usage NULL
#' @returns NULL
#' 
#' @templateVar .TITLE Logarithmic Loss
#' @templateVar .FUN logloss
#' @templateVar .TASK Classification
#' @templateVar .METHOD matrix
#' @template classification_entropy_template
#' 
#' @inheritDotParams logloss.integer
#' @inheritDotParams weighted.logloss.integer
#' @inheritDotParams logloss.factor
#' @inheritDotParams weighted.logloss.factor
#' 
#' @export
logloss <- function(...) {
  UseMethod(
    generic = "logloss"
  )
}

#' @rdname logloss
#' @usage
#' ## Generic S3 method
#' ## for weighted Logarithmic Loss
#' weighted.logloss(...)
#' 
#' @export
weighted.logloss <- function(...) {
  UseMethod(
    generic = "weighted.logloss"
  )
}

# script end;
