# script: Mean Absolute Percentage Error
# date: 2024-10-10
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate Methods
# script start;

#' @title NULL
#' @usage NULL
#' @returns NULL
#' 
#' @templateVar .TITLE mean absolute percentage error
#' @templateVar .FUN mape
#' @template regression_standard_template
#' @template regression_standard_params
#' 
#' @export
mape <- function(...) {
  UseMethod(
    generic = "mape"
  )
}

#' @rdname mape
#' @usage
#' ## Generic S3 method
#' ## for weighted Mean Absolute Percentage Error
#' weighted.mape(...)
#' @export
weighted.mape <- function(...) {
  UseMethod(
    generic = "weighted.mape"
  )
}

# script end;
