# script: Brier Score
# date: 2025-04-16
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate methods for accuracy
# script start;

#' @title NULL
#' @usage NULL
#' @returns NULL
#' 
#' @templateVar .TITLE Brier Score
#' @templateVar .FUN brier
#' @templateVar .TASK Classification
#' @template classification_proper_template
#'
#' @export
brier <- function(...) {
  UseMethod(
    generic = "brier"
  )
}

#' @rdname brier
#' @usage
#' ## Generic S3 method
#' ## for weighted Brier Score
#' weighted.brier(...)
#' @export
weighted.brier <- function(...) {
  UseMethod(
    generic = "weighted.brier"
  )
}

# script end;
