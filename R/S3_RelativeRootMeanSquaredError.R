# script: Relative Root Mean Squared Error
# date: 2024-12-27
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate Errors
# script start;

#' @title NULL
#' @usage NULL
#' @return NULL
#' 
#' @templateVar .TITLE Relative Root Mean Squared Error
#' @templateVar .FUN rrmse
#' @template regression_standard_template
#' @template regression_standard_params
#' @usage NULL
#' 
#' @export
rrmse <- function(...) {
  UseMethod(
    generic = "rrmse"
  )
}

#' @rdname rrmse
#' @usage
#' ## Generic S3 method
#' ## for weighted Relative Root Mean Squared Error
#' weighted.rrmse(...)
#' @export
weighted.rrmse <- function(...) {
  UseMethod(
    generic = "weighted.rrmse"
  )
}

# script end;
