# script: Root Mean Squared Logarithmic Error
# date: 2024-10-09
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate Methods
# script start;

#' @title NULL
#' @usage NULL
#' 
#' @templateVar .TITLE Root Mean Squared Logarithmic Error
#' @templateVar .FUN rmsle
#' @template regression_standard_template
#' @template regression_standard_params
#' 
#' @export
rmsle <- function(...) {
  UseMethod(
    generic = "rmsle"
  )
}

#' @rdname rmsle
#' @usage
#' ## Generic S3 method
#' ## for weighted Root Mean Squared Logarithmic Error
#' weighted.rmsle(...)
#' @export
weighted.rmsle <- function(...) {
  UseMethod(
    generic = "weighted.rmsle"
  )
}

# script end;
