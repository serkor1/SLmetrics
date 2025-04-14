# script: Mean Absolute Error
# date: 2024-10-10
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate Methods
# script start;

#' @title NULL
#' @usage NULL
#' @returns NULL
#' 
#' @templateVar .TITLE Huber Loss Function
#' @templateVar .FUN mae
#' @template regression_standard_template
#' @template regression_standard_params
#' 
#' @export
mae <- function(...) {
  UseMethod(
    generic = "mae"
  )
}

#' @rdname mae
#' @usage
#' ## Generic S3 method
#' ## for unweighted Mean Absolute Error
#' weighted.mae(...)
#' @export
weighted.mae <- function(...) {
  UseMethod(
    generic = "weighted.mae"
  )
}

# script end;
