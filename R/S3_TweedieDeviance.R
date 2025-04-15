# script: Tweedie Deviance
# date: 2025-04-15
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate Errors
# script start;

#' @title NULL
#' @usage NULL
#' @returns NULL
#'
#' @templateVar .TITLE Tweedie Deviance
#' @templateVar .FUN tweedie.deviance
#' @template regression_standard_template
#' @template regression_standard_params
#' @usage NULL
#'
#' @export
tweedie.deviance <- function(...) {
    UseMethod(
        generic = "tweedie.deviance"
    )
}

#' @rdname tweedie.deviance
#' @usage
#' ## Generic S3 method
#' ## for weighted Root Mean
#' ## Squared Error
#' weighted.tweedie.deviance(...)
#' @export
weighted.tweedie.deviance <- function(...) {
    UseMethod(
        generic = "weighted.tweedie.deviance"
    )
}

# script end;
