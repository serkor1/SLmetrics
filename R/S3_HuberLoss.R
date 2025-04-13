# script: Huber Loss
# date: 2024-10-09
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate Methods
# script start;

#' @usage NULL
#' @title NULL
#' 
#' @templateVar .TITLE Huber Loss Function
#' @templateVar .FUN huberloss
#' @template regression_standard_template
#' @template regression_standard_params
#' 
#' @export
huberloss <- function(...) {
  UseMethod(
    generic = "huberloss"
  )
}

#' @rdname huberloss
#' @usage
#' ## Generic S3 method
#' ## for weighted Huber Loss
#' weighted.huberloss(...)
#' @export
weighted.huberloss <- function(...) {
  UseMethod(
    generic = "weighted.huberloss"
  )
}

# script end;
