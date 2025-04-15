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
#' @templateVar .FUN deviance.tweedie
#' @template regression_standard_template
#' @template regression_standard_params
#' @usage NULL
#'
#' @rawNamespace export(deviance.tweedie)
deviance.tweedie <- function(...) {
    UseMethod(
        generic = "deviance.tweedie"
    )
}

#' @rdname deviance.tweedie
#' @usage
#' ## Generic S3 method
#' ## for weighted Root Mean
#' ## Squared Error
#' weighted.deviance.tweedie(...)
#' @rawNamespace export(weighted.deviance.tweedie)
weighted.deviance.tweedie <- function(...) {
    UseMethod(
        generic = "weighted.deviance.tweedie"
    )
}

# script end;
