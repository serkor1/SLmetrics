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
#' @templateVar .FUN gamma.deviance
#' @template regression_standard_template
#' @template regression_standard_params
#' @usage NULL
#'
#' @export
gamma.deviance <- function(...) {
    UseMethod(
        generic = "gamma.deviance"
    )
}

#' @rdname gamma.deviance
#' @usage
#' ## Generic S3 method
#' ## for weighted Root Mean
#' ## Squared Error
#' weighted.gamma.deviance(...)
#' @export
weighted.gamma.deviance <- function(...) {
    UseMethod(
        generic = "weighted.gamma.deviance"
    )
}

# script end;
