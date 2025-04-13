# script:Symmetric Mean Absolute Error
# date: 2024-10-10
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate Methods
# script start;

#' @usage NULL
#' @title NULL
#' 
#' @templateVar .TITLE Symmetric Mean Absolutte Percentage Error
#' @templateVar .FUN smape
#' @template regression_standard_template
#' @template regression_standard_params
#' 
#' @export
smape <- function(...) {
  UseMethod(
    generic = "smape"
  )
}

#' @rdname smape
#' @usage
#' ## Generic S3 method
#' ## for weighted Symmetric Mean Absolutte Percentage Error
#' weighted.smape(...)
#' @export
weighted.smape <- function(...) {
  UseMethod(
    generic = "weighted.smape"
  )
}


# script end;
