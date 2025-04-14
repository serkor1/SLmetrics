# script: Concordance Correlation Coefficient
# date: 2024-10-10
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate Methods
# script start;

#' @title NULL
#' @usage NULL
#' @returns NULL
#' 
#' @templateVar .TITLE concordance correlation coefficient
#' @templateVar .FUN ccc
#' @template regression_standard_template
#' @template regression_standard_params
#' 
#' @export
ccc <- function(...) {
  UseMethod(
    generic = "ccc",
    object  = ..1
  )
}

#' @rdname ccc
#' @usage
#' weighted.ccc(...)
#' @export
weighted.ccc <- function(...) {
  UseMethod(
    generic = "weighted.ccc",
    object  = ..1
  )
}

# script end;
