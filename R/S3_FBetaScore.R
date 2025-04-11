# script: fbetascore
# date: 2024-10-01
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate methods
# script start; 

#' @templateVar .TITLE \eqn{F_{\beta}}-score
#' @templateVar .FUN fbeta
#' @templateVar .TASK Classification
#' @template classification_inheritDotParams
#' @template classification_factor_example
#' @template classification_cmatrix_template
#' 
#' @usage
#' ## Generic S3 method
#' ## for unweighted F-beta
#' fbeta(...)
#' 
#' @param beta A <[numeric]> vector of [length] \eqn{1} (default: \eqn{1}).
#' 
#' @family Classification
#' @family Supervised Learning
#' 
#' @export
fbeta <- function(...) {
  UseMethod(
    generic = "fbeta",
    object  = ..1
  )
}

#' @rdname fbeta
#' @usage
#' ## Generic S3 method
#' ## for weighted F-beta
#' weighted.fbeta(...)
#' @export
weighted.fbeta <- function(...) {
  UseMethod(
    generic = "weighted.fbeta",
    object  = ..1
  )
}

# script end;
