# script: Root Mean Squared Error
# date: 2024-10-09
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate Errors
# script start;

#' @templateVar .TITLE root mean squared error
#' @templateVar .FUN rmse
#' @template regression_standard_template
#' @template regression_standard_params
#' @usage NULL
#' 
#' @export
rmse <- function(...) {
  UseMethod(
    generic = "rmse"
  )
}

#' @rdname rmse
#' @usage
#' ## Generic S3 method
#' ## for weighted Root Mean
#' ## Squared Error
#' weighted.rmse(...)
#' @export
weighted.rmse <- function(...) {
  UseMethod(
    generic = "weighted.rmse"
  )
}

# script end;
