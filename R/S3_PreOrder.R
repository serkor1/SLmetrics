# script: Ordering of containers
# date: 2025-04-19
# author: Serkan Korkmaz
# objective: Generate S3 methods
# for ordering containers
# script start;

#' @usage NULL
#' @title NULL
#' 
#' @templateVar .TITLE Preorder matrices
#' @templateVar .OBJECTIVE Somehting long
#' @templateVar .FUN preorder
#' @templateVar .DEFENSE true
#' 
#' @template generic_utils
#' 
#' @inheritDotParams preorder.matrix
#' 
#' @returns 
#' A container of sorted indices
#' 
#' @export
preorder <- function(...) {
  UseMethod(
    generic = "preorder"
  )
}

# script end;