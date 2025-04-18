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
#' @templateVar .TASK regression
#' 
#' @template generic_description
#' @template regression_standard_template
#' 
#' @rawNamespace export(deviance.tweedie)
deviance.tweedie <- function(...) {
    UseMethod(
        generic = "deviance.tweedie"
    )
}

#' @usage NULL
#' 
#' @templateVar .TITLE Tweedie Deviance
#' @templateVar .FUN deviance.tweedie
#' @templateVar .TASK regression
#' 
#' @template generic_inherit
#' 
#' @rawNamespace export(weighted.deviance.tweedie)
weighted.deviance.tweedie <- function(...) {
    UseMethod(
        generic = "weighted.deviance.tweedie"
    )
}

# script end;
