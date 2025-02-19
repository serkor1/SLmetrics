# script: False Positive Rate
# date: 2024-10-07
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate Methods
# for False Positive Rate
# script start;

#' @aliases fpr fallout
#' @inherit specificity
#' 
#' @title False Positive Rate
#'
#' @description
#' A generic function for the [False Positive Rate](https://en.wikipedia.org/wiki/False_positive_rate). Use [weighted.fpr()] for the weighted [False Positive Rate](https://en.wikipedia.org/wiki/False_positive_rate).
#' 
#' ## Other names
#' Fallout
#' 
#' @usage 
#' ## Generic S3 method
#' fpr(
#'  ...,
#'  micro = NULL,
#'  na.rm = TRUE
#' )
#' 
#' @section Definition:
#' Let \eqn{\hat{\gamma} \in [0, 1]} be the proportion of false positives among the actual negatives. The false positive rate of the classifier is calculated as,
#'
#' \deqn{
#'   \hat{\gamma} = \frac{\#FP_k}{\#TN_k + \#FP_k}
#' }
#'
#' Where:
#' 
#' - \eqn{\#TN_k} is the number of true negatives, and
#' - \eqn{\#FP_k} is the number of false positives.
#'
#' @example man/examples/scr_FalsePositiveRate.R
#' 
#' @family Classification
#' @family Supervised Learning
#'
#' @export
fpr <- function(
  ..., 
  micro = NULL, 
  na.rm = TRUE) {
  UseMethod(
    generic = "fpr",
    object  = ..1
  )
}

#' @rdname fpr
#' @usage
#' ## Generic S3 method
#' fallout(
#'  ...,
#'  micro = NULL,
#'  na.rm = TRUE
#' )
#' @export
fallout <- function(
  ..., 
  micro = NULL, 
  na.rm = TRUE) {
  UseMethod(
    generic = "fallout",
    object  = ..1
  )
}

#' @rdname fpr
#' @usage
#' ## Generic S3 method
#' weighted.fpr(
#'  ...,
#'  w,
#'  micro = NULL,
#'  na.rm = TRUE
#' )
#' @export
weighted.fpr <- function(
  ...,
  w,
  micro = NULL, 
  na.rm = TRUE) {
  UseMethod(
    generic = "weighted.fpr",
    object  = ..1
  )
}

#' @rdname fpr
#' @usage
#' ## Generic S3 method
#' weighted.fallout(
#'  ...,
#'  w,
#'  micro = NULL,
#'  na.rm = TRUE
#' )
#' @export
weighted.fallout <- function(
  ...,
  w,
  micro = NULL, 
  na.rm = TRUE) {
  UseMethod(
    generic = "weighted.fallout",
    object  = ..1
  )
}

# script end;
