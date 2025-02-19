# script: recall
# date: 2024-09-29
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate method
# script start;

#' @aliases sensitivity tpr recall
#' @inherit specificity
#' @title Recall
#' 
#' @description
#' A generic funcion for the [Recall](https://en.wikipedia.org/wiki/Sensitivity_and_specificity). Use [weighted.fdr()] for the weighted [Recall](https://en.wikipedia.org/wiki/Sensitivity_and_specificity).
#' 
#' ## Other names
#' Sensitivity, True Positive Rate
#' 
#' @usage
#' ## Generic S3 method
#' recall(
#'  ...,
#'  micro = NULL,
#'  na.rm = TRUE
#' )
#' 
#' @section Definition:
#' Let \eqn{\hat{\rho} \in [0, 1]} be the proportion of true positives among the actual positives. The recall of the classifier is calculated as,
#'
#' \deqn{
#'   \hat{\rho} = \frac{\#TP_k}{\#TP_k + \#FN_k}
#' }
#'
#' Where:
#' 
#' - \eqn{\#TP_k} is the number of true positives, and
#' - \eqn{\#FN_k} is the number of false negatives.
#'
#' @example man/examples/scr_Recall.R
#'
#' @family Classification
#' @family Supervised Learning
#' 
#' @export
recall <- function(
  ..., 
  micro = NULL, 
  na.rm = TRUE) {
  UseMethod(
    generic = "recall",
    object  = ..1
  )
}

#' @rdname recall
#' @usage
#' ## Generic S3 method
#' sensitivity(
#'  ...,
#'  micro = NULL,
#'  na.rm = TRUE
#' )
#' @export
sensitivity <- function(
  ..., 
  micro = NULL, 
  na.rm = TRUE) {
  UseMethod(
    generic = "sensitivity",
    object  = ..1
  )
}

#' @rdname recall
#' @usage
#' ## Generic S3 method
#' tpr(
#'  ...,
#'  micro = NULL,
#'  na.rm = TRUE
#' )
#' @export
tpr <- function(
  ..., 
  micro = NULL, 
  na.rm = TRUE) {
  UseMethod(
    generic = "tpr",
    object  = ..1
  )
}


#' @rdname recall
#' @usage
#' ## Generic S3 method
#' weighted.recall(
#'  ...,
#'  w,
#'  micro = NULL,
#'  na.rm = TRUE
#' )
#' @export
weighted.recall <- function(
  ..., 
  w, 
  micro = NULL, 
  na.rm = TRUE) {
  UseMethod(
    generic = "weighted.recall",
    object  = ..1
  )
}

#' @rdname recall
#' @usage
#' ## Generic S3 method
#' weighted.sensitivity(
#'  ...,
#'  w,
#'  micro = NULL,
#'  na.rm = TRUE
#' )
#' @export
weighted.sensitivity <- function(
  ..., 
  w, 
  micro = NULL, 
  na.rm = TRUE) {
  UseMethod(
    generic = "weighted.sensitivity",
    object  = ..1
  )
}

#' @rdname recall
#' @usage
#' ## Generic S3 method
#' weighted.tpr(
#'  ...,
#'  w,
#'  micro = NULL,
#'  na.rm = TRUE
#' )
#' @export
weighted.tpr <- function(
  ..., 
  w, 
  micro = NULL, 
  na.rm = TRUE) {
  UseMethod(
    generic = "weighted.tpr",
    object  = ..1
  )
}

# script end;
