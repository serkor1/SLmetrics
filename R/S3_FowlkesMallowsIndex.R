# script: Fowlkes-Mallows Index
# date: 2024-10-07
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate methods
# script start;

#' @title NULL
#' @usage NULL
#' @returns NULL
#' 
#' @templateVar .TITLE Fowlkes Mallows Index
#' @templateVar .FUN fmi
#' @templateVar .TASK Classification
#' @templateVar .MULTI_OUTPUT false
#' @template classification_standard_template
#' 
#' @export
fmi <- function(...) {
  UseMethod(
    generic = "fmi",
    object  = ..1
  )
}

#' @rdname fmi
#' @usage
#' ## Generic S3 method
#' ## for weighted Fowlkes
#' ## Mallows Index
#' weighted.fmi(...)
#' @export
weighted.fmi <- function(...) {
  UseMethod(
    generic = "weighted.fmi",
    object  = ..1
  )
}

# script end;
