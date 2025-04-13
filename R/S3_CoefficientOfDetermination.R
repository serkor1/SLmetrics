# script: Coefficient of Determination
# date: 2024-10-10
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate Methods
# script start;

#' @usage NULL
#' @title NULL
#' 
#' @templateVar .TITLE \eqn{R^2}
#' @templateVar .FUN rsq
#' @template regression_standard_template
#' @template regression_standard_params
#' 
#' @export
rsq <- function(
  ..., 
  k = 0) {
  UseMethod(
    generic = "rsq",
    object  = ..1
  )
}

#' @rdname rsq
#' @usage
#' ## Generic S3 method
#' ## for weighted \eqn{R^2}
#' weighted.rsq(
#'  ...,
#'  w,
#'  k = 0
#' )
#' @export
weighted.rsq <- function(
  ...,
  w,
  k = 0) {
  UseMethod(
    generic = "weighted.rsq",
    object  = ..1
  )
}

# script end;
