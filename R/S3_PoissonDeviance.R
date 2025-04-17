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
#' @templateVar .FUN deviance.poisson
#' @template regression_standard_template
#' @template regression_standard_params
#' @usage NULL
#'
#' @rawNamespace export(deviance.poisson)
deviance.poisson <- function(...) {
    UseMethod(
        generic = "deviance.poisson"
    )
}

#' @rdname deviance.poisson
#' @usage
#' ## Generic S3 method
#' ## for weighted Root Mean
#' ## Squared Error
#' weighted.deviance.poisson(...)
#' @rawNamespace export(weighted.deviance.poisson)
weighted.deviance.poisson <- function(...) {
    UseMethod(
        generic = "weighted.deviance.poisson"
    )
}

# script end;
