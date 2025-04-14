# script: Relative Absolute Error
# date: 2024-10-11
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate Methods
# script start;

#' @title NULL
#' @usage NULL
#' @returns NULL
#' 
#' @templateVar .TITLE Relative Absolute Error
#' @templateVar .FUN rae
#' @template regression_standard_template
#' @template regression_standard_params
#' 
#' @export
rae <- function(...) {
  UseMethod(
    generic = "rae"
  )
}

#' @rdname rae
#' @usage
#' ## Generic S3 method
#' ## for weighted Relative Absolute Error
#' weighted.rae(...)
#' @export
weighted.rae <- function(...) {
  UseMethod(
    generic = "weighted.rae"
  )
}

# script end;
