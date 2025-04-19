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
#' @templateVar .TASK regression
#' 
#' @template generic_description
#' @template regression_standard_template
#' 
#' @rawNamespace export(deviance.poisson)
deviance.poisson <- function(...) {
    UseMethod(
        generic = "deviance.poisson"
    )
}

#' @usage NULL
#' 
#' @templateVar .TITLE Poisson Deviance
#' @templateVar .FUN deviance.poisson
#' @templateVar .TASK regression
#' 
#' @template generic_inherit
#' 
#' @rawNamespace export(weighted.deviance.poisson)
weighted.deviance.poisson <- function(...) {
    UseMethod(
        generic = "weighted.deviance.poisson"
    )
}

# script end;
