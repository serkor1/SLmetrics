# script: Poisson Deviance
# date: 2025-04-15
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate Errors
# script start;

#' @title NULL
#' @usage NULL
#' @returns NULL
#'
#' @templateVar .TITLE Poisson Deviance
#' @templateVar .FUN poisson.deviance
#' @template regression_standard_template
#' @template regression_standard_params
#' @usage NULL
#'
#' @export
poisson.deviance <- function(...) {
    UseMethod(
        generic = "poisson.deviance"
    )
}

#' @rdname poisson.deviance
#' @usage
#' ## Generic S3 method
#' ## for weighted Root Mean
#' ## Squared Error
#' weighted.poisson.deviance(...)
#' @export
weighted.poisson.deviance <- function(...) {
    UseMethod(
        generic = "weighted.poisson.deviance"
    )
}

# script end;
