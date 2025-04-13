# script: Mean Percentage Error
# date: 2024-10-10
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate Methods
# script start;

#' @usage NULL
#' @title NULL
#' 
#' @templateVar .TITLE mean percentage error
#' @templateVar .FUN mpe
#' @template regression_standard_template
#' @template regression_standard_params
#' 
#' @export
mpe <- function(...) {
  UseMethod(
    generic = "mpe"
  )
}

#' @rdname mpe
#' @usage
#' ## Generic S3 method
#' ## for weighted Mean Percentage Error
#' weighted.mpe(...)
#' @export
weighted.mpe <- function(...) {
  UseMethod(
    generic = "weighted.mpe"
  )
}

# script end;
