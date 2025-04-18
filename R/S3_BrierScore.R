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
#' @templateVar .FUN brier.score
#' @templateVar .TASK Classification
#' @template classification_proper_template
#'
#' @export
brier.score <- function(...) {
  UseMethod(
    generic = "brier.score"
  )
}

#' @rdname brier.score
#' @usage
#' ## Generic S3 method
#' ## for weighted Brier Score
#' weighted.brier.score(...)
#' @export
weighted.brier.score <- function(...) {
  UseMethod(
    generic = "weighted.brier.score"
  )
}

# script end;
