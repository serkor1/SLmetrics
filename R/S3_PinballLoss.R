# script: Pinball Loss
# date: 2024-10-13
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate Methods
# script start;

#' @title NULL
#' @usage NULL
#' @return NULL
#' 
#' @templateVar .TITLE pinball loss
#' @templateVar .FUN pinball
#' @template regression_standard_template
#' @template regression_standard_params
#' 
#' @export
pinball <- function(...) {
  UseMethod(
    generic = "pinball"
  )
}

#' @rdname pinball
#' @usage
#' ## Generic S3 method
#' ## for weighted Pinball Loss
#' weighted.pinball(...)
#' @export
weighted.pinball <- function(...) {
  UseMethod(
    generic = "weighted.pinball"
  )
}

# script end;
