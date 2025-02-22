# script: Area Under the  Curve
# author: Serkan Korkmaz, serkor1@duck.com
# date: 2025-22-02
# objective: Generate method
# script start;

#' @title AUC
#' 
#' @description
#' The [auc()]-function calculates the area under the curve.
#' 
#' @usage
#' ## Generic S3 method
#' auc(
#'  y,
#'  x,
#'  method = 0,
#'  ordered = TRUE,
#'  ...
#' )
#' 
#' @param y A <[numeric]> vector of [length] \eqn{n}.
#' @param x A <[numeric]> vector of [length] \eqn{n}.
#' @param method A <[numeric]> value (default: \eqn{0}). Defines the underlying method of calculating the area under the curve. If \eqn{0} it is calculated using the `trapezoid`-method, if \eqn{1} it is calculated using the `step`-method.
#' @param ordered A <[logical]> value (default: [TRUE]). If [FALSE] the `x` and `y` pair will be ordered before calculating the area under the curve.
#' @param ... Arguments passed into other methods.
#' 
#' @returns 
#' A <[numeric]>  vector  of [length] 1
#' 
#' @example man/examples/scr_AreaUnderTheCurve.R
#' 
#' @family Tools
#' 
#' @export
auc <- function(
  y,
  x,
  method  = 0,
  ordered = TRUE,
  ...) {
  UseMethod(
    generic = "auc"
  )
}

# script end;
