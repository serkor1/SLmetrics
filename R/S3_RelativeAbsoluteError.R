# script: Relative Absolute Error
# date: 2024-10-11
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate Methods
# script start;

#' @usage NULL
#' @title NULL
#' 
#' @templateVar .TITLE Relative Absolute Error
#' @templateVar .FUN rae
#' @template regression_standard_template
#' @template regression_standard_params
#' 
#' @export
rae <- function(
  actual,
  predicted,
  ...) {
  UseMethod(
    generic = "rae"
  )
}

#' @rdname rae
#' @usage
#' ## Generic S3 method
#' ## for weighted Relative Absolute Error
#' weighted.rae(
#'  actual,
#'  predicted,
#'  w,
#'  ...
#' )
#' @export
weighted.rae <- function(
  actual,
  predicted,
  w,
  ...) {
  UseMethod(
    generic = "weighted.rae"
  )
}

# script end;
