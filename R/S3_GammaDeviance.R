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
#' @templateVar .TASK regression
#' 
#' @template generic_description
#' @template regression_standard_template
#' 
#' @rawNamespace export(deviance.gamma)
deviance.gamma <- function(...) {
    UseMethod(
        generic = "deviance.gamma"
    )
}

#' @usage NULL
#' 
#' @templateVar .TITLE Gamma Deviance
#' @templateVar .FUN deviance.gamma
#' @templateVar .TASK regression
#' 
#' @template generic_inherit
#' 
#' @rawNamespace export(weighted.deviance.gamma)
weighted.deviance.gamma <- function(...) {
    UseMethod(
        generic = "weighted.deviance.gamma"
    )
}

# script end;
