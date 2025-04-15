# script: Gamma Deviance
# date: 2025-04-15
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate Errors
# script start;

#' @title NULL
#' @usage NULL
#' @returns NULL
#'
#' @templateVar .TITLE Gamma Deviance
#' @templateVar .FUN deviance.gamma
#' @template regression_standard_template
#' @template regression_standard_params
#' @usage NULL
#'
#' @rawNamespace export(deviance.gamma)
deviance.gamma <- function(...) {
    UseMethod(
        generic = "deviance.gamma"
    )
}

#' @rdname deviance.gamma
#' @usage
#' ## Generic S3 method
#' ## for weighted Root Mean
#' ## Squared Error
#' weighted.deviance.gamma(...)
#' @rawNamespace export(weighted.deviance.gamma)
weighted.deviance.gamma <- function(...) {
    UseMethod(
        generic = "weighted.deviance.gamma"
    )
}

# script end;
