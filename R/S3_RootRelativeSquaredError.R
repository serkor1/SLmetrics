# script: Root Relative Squared Error
# date: 2024-10-11
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Genereate Methods
# script start;

#' @title NULL
#' @usage NULL
#' @returns NULL
#' 
#' @templateVar .TITLE Root Relative Squared Error
#' @templateVar .FUN rrse
#' @template regression_standard_template
#' @template regression_standard_params
#' 
#' @export
rrse <- function(...) {
  UseMethod(
    generic = "rrse"
  )
}

#' @rdname rrse
#' @usage
#' ## Generic S3 method
#' ## for weighted Root Relative Squared Error
#' weighted.rrse(...)
#' @export
weighted.rrse <- function(...) {
  UseMethod(
    generic = "weighted.rrse"
  )
}

# script end;
