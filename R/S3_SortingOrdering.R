# script: presort
# date: 2025-03-12
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate methods for presorting
# matrices

#' @title Presort
#' 
#' @description
#' This generic function does a column-wise sorting of a [numeric] or [integer] matrix.
#' 
#' @usage
#' presort(
#'  x,
#'  decreasing = FALSE,
#'  ...
#' )
#' 
#' @param x a [numeric] or [integer] matrix to be sorted.
#' @param decreasing a [logical] value of [length] 1 (default: [FALSE]). If [TRUE] the matrix is return in descending order.
#' @param ... Arguments passed into other methods.
#' 
#' @example man/examples/scr_SortingOrdering.R
#' 
#' @family Tools
#' 
#' @returns
#' A [matrix] with sorted rows.
#' 
#' @export
presort <- function(
  x,
  decreasing = FALSE,
  ...) {
  UseMethod(
    generic = "presort",
    object  = x 
  )
}

#' @inherit presort
#' 
#' @title Preorder
#' 
#' @description
#' This function does a column-wise ordering permutation of [numeric] or [integer] matrix.
#' 
#' @usage
#' preorder(
#'  x,
#'  decreasing = FALSE,
#'  ...
#' )
#' 
#' @family Tools
#' 
#' @returns
#' A [matrix] with indices to the ordered values.
#' 
#' @export
preorder <- function(
  x,
  decreasing = FALSE,
  ...) {
  UseMethod(
    generic = "preorder",
    object  = x 
  )
}
