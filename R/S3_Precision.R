# script: precision
# date: 2024-10-01
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate method
# script start;

#' @aliases precision ppv
#' @inherit specificity
#' 
#' @title Precision
#'
#' @description
#' A generic funcion for the [precision](https://en.wikipedia.org/wiki/Positive_and_negative_predictive_values). Use [weighted.fdr()] for the weighted [precision](https://en.wikipedia.org/wiki/Positive_and_negative_predictive_values).
#' 
#' ## Other names
#' Positive Predictive Value
#' 
#' @usage
#' ## Generic S3 method
#' precision(
#'  ...,
#'  micro = NULL,
#'  na.rm = TRUE
#' )
#' 
#' @section Definition:
#' Let \eqn{\hat{\pi} \in [0, 1]} be the proportion of true positives among the predicted positives. The precision of the classifier is calculated as,
#'
#' \deqn{
#'   \hat{\pi} = \frac{\#TP_k}{\#TP_k + \#FP_k}
#' }
#'
#' Where:
#' 
#' - \eqn{\#TP_k} is the number of true positives, and
#' - \eqn{\#FP_k} is the number of false positives.
#'
#' @example man/examples/scr_Precision.R
#'
#' @family Classification
#' @family Supervised Learning
#'
#' @export
precision <- function(
  ..., 
  micro = NULL, 
  na.rm = TRUE) {
  UseMethod(
    generic = "precision",
    object  = ..1
  )
}

#' @rdname precision
#' @usage
#' ## Generic S3 method
#' weighted.precision(
#'  ...,
#'  w,
#'  micro = NULL,
#'  na.rm = TRUE
#' )
#' @export
weighted.precision <- function(
  ..., 
  w,
  micro = NULL, 
  na.rm = TRUE) {
  UseMethod(
    generic = "weighted.precision",
    object  = ..1
  )
}

#' @rdname precision
#' @usage
#' ## Generic S3 method
#' ppv(
#'  ...,
#'  micro = NULL,
#'  na.rm = TRUE
#' )
#' @export
ppv <- function(
  ..., 
  micro = NULL, 
  na.rm = TRUE) {
  UseMethod(
    generic = "ppv",
    object  = ..1
  )
}

#' @rdname precision
#' @usage
#' ## Generic S3 method
#' weighted.ppv(
#'  ...,
#'  w,
#'  micro = NULL,
#'  na.rm = TRUE
#' )
#' @export
weighted.ppv <- function(
  ...,
  w,
  micro = NULL, 
  na.rm = TRUE) {
  UseMethod(
    generic = "weighted.ppv",
    object  = ..1
  )
}

# script end;
