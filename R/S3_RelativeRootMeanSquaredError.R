# script: Relative Root Mean Squared Error
# date: 2024-12-27
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate Errors
# script start;

#' @templateVar .TITLE Relative Root Mean Squared Error
#' @templateVar .FUN rrmse
#' @template regression_standard_template
#' @template regression_standard_params
#' @usage NULL
#' 
#' @export
rrmse <- function(
  actual,
  predicted,
  normalization = 1,
  ...) {
  UseMethod(
    generic = "rrmse"
  )
}

#' @rdname rrmse
#' @usage
#' ## Generic S3 method
#' ## for weighted Relative Root Mean Squared Error
#' weighted.rrmse(
#'  actual,
#'  predicted,
#'  w,
#'  normalization = 1,
#'  ...
#' )
#' @export
weighted.rrmse <- function(
  actual,
  predicted,
  w,
  normalization = 1,
  ...) {
  UseMethod(
    generic = "weighted.rrmse"
  )
}

# script end;
