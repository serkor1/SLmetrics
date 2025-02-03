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
#' A generic funcion for the [False Positive Rate](https://en.wikipedia.org/wiki/False_positive_rate). Use [weighted.fpr()] for the weighted [False Positive Rate](https://en.wikipedia.org/wiki/False_positive_rate).
#' 
#' ## Other names
#' Fallout
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
fpr <- function(...) {
  UseMethod(
    generic = "fpr",
    object  = ..1
  )
}

#' @rdname fpr
#' @export
fallout <- function(...) {
  UseMethod(
    generic = "fallout",
    object  = ..1
  )
}

#' @rdname fpr
#' @export
weighted.fpr <- function(...) {
  UseMethod(
    generic = "weighted.fpr",
    object  = ..1
  )
}

#' @rdname fpr
#' @export
weighted.fallout <- function(...) {
  UseMethod(
    generic = "weighted.fallout",
    object  = ..1
  )
}

# script end;
