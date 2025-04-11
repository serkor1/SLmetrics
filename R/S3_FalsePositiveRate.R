# script: False Positive Rate
# date: 2024-10-07
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate Methods
# for False Positive Rate
# script start;

#' @aliases fallout weighted.fallout
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
#' ## for unweighted false
#' ## positive rate
#' fpr(...)
#' 
#' @templateVar .FUN fpr
#' @template classification_inheritDotParams
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
#' @templateVar .FUN fpr
#' @template classification_factor_example
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
#' @usage
#' ## Generic S3 method
#' ## for weighted false positive
#' ## rate
#' weighted.fpr(...)
#' @export
weighted.fpr <- function(...) {
  UseMethod(
    generic = "weighted.fpr",
    object  = ..1
  )
}

#' @export
fallout <- function(...) {
  UseMethod(
    generic = "fallout",
    object  = ..1
  )
}

#' @export
weighted.fallout <- function(...) {
  UseMethod(
    generic = "weighted.fallout",
    object  = ..1
  )
}

# script end;
