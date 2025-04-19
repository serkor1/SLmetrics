# script: Ordering of containers
# date: 2025-04-19
# author: Serkan Korkmaz
# objective: Generate S3 methods
# for ordering containers
# script start;

#' @usage NULL
#' @title NULL
#' 
#' @templateVar .TITLE Presort matrices
#' @templateVar .OBJECTIVE Somehting long
#' @templateVar .FUN presort
#' @templateVar .DEFENSE true
#' 
#' @template generic_utils
#' 
#' @inheritDotParams presort.matrix
#' 
#' @returns
#' A sorted container
#' 
#' @export
presort <- function(...) {
  UseMethod(
    generic = "presort"
  )
}

# script end;