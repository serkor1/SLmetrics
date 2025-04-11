# script: Negative Predictive Value
# date: 2024-10-07
# author: Serkan Korkmaz, serkor1@duck.com
# objective:
# script start;

#' @aliases tnr selectivity weighted.tnr weighted.selectivity
#' @templateVar .TITLE specificity
#' @templateVar .FUN specificity
#' @templateVar .TASK Classification
#' @template classification_inheritDotParams
#' @template classification_factor_example
#' @template classification_cmatrix_template
#' 
#' @usage 
#' ## Generic S3 method
#' ## for unweighted Negative
#' ## Predictive Value
#' npv(...)
#'
#' @family Classification
#' @family Supervised Learning
#'
#' @export
npv <- function(...) {
  UseMethod(
    generic = "npv",
    object  = ..1
  )
}

#' @rdname npv
#' @usage 
#' ## Generic S3 method
#' ## for weighted Negative
#' ## Predictive Value
#' npv(...)
#' @export
weighted.npv <- function(...) {
  UseMethod(
    generic = "weighted.npv",
    object  = ..1
  )
}

# script end;
