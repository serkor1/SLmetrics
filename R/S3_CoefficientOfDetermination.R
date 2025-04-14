# script: Coefficient of Determination
# date: 2024-10-10
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate Methods
# script start;

#' @title NULL
#' @usage NULL
#' @returns NULL
#' 
#' @templateVar .TITLE \eqn{R^2}
#' @templateVar .FUN rsq
#' @template regression_standard_template
#' @template regression_standard_params
#' 
#' @export
rsq <- function(...) {
  UseMethod(
    generic = "rsq",
    object  = ..1
  )
}

#' @rdname rsq
#' @usage
#' ## Generic S3 method
#' ## for weighted \eqn{R^2}
#' weighted.rsq(...)
#' @export
weighted.rsq <- function(...) {
  UseMethod(
    generic = "weighted.rsq",
    object  = ..1
  )
}

# script end;
