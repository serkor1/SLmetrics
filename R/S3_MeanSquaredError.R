# script: Mean Squared Error
# date: 2024-10-09
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate Errors
# script start;

#' @usage NULL
#' @title NULL
#' 
#' @templateVar .TITLE mean squeared error
#' @templateVar .FUN huberloss
#' @template regression_standard_template
#' @template regression_standard_params
#' 
#' @export
mse <- function(...) {
  UseMethod(
    generic = "mse"
  )
}

#' @rdname mse
#' @usage
#' ## Generic S3 method
#' ## for weighted Mean Squared Error
#' weighted.mse(
#'  actual,
#'  predicted,
#'  w,
#'  ...
#' )
#' @export
weighted.mse <- function(...) {
  UseMethod(
    generic = "weighted.mse"
  )
}

# script end;
