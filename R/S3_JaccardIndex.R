# script: Jaccard Methods
# date: 2024-10-06
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Create Methods
# script start;

#' @aliases jaccard csi tscore
#' @inherit specificity
#' 
#' @title Jaccard Index
#'
#' @description
#' The [jaccard()]-function computes the [Jaccard Index](https://en.wikipedia.org/wiki/Jaccard_index), also known as the Intersection over Union, between
#' two vectors of predicted and observed [factor()] values. The [weighted.jaccard()] function computes the weighted Jaccard Index.
#'
#' @usage
#' ## Generic S3 method
#' jaccard(
#'  ...,
#'  micro = NULL,
#'  na.rm = TRUE
#' )
#' 
#' @section Definition:
#'
#' The metric is calculated for each class \eqn{k} as follows,
#'
#' \deqn{
#'   \frac{\#TP_k}{\#TP_k + \#FP_k + \#FN_k}
#' }
#'
#' Where \eqn{\#TP_k}, \eqn{\#FP_k}, and \eqn{\#FN_k} represent the number of true positives, false positives, and false negatives for each class \eqn{k}, respectively.
#' 
#' @example man/examples/scr_JaccardIndex.R
#'
#' @family Classification
#' @family Supervised Learning
#'
#' @export
jaccard <- function(
  ..., 
  micro = NULL, 
  na.rm = TRUE) {
  UseMethod(
    generic = "jaccard",
    object  = ..1
  )
}

#' @rdname jaccard
#' @usage
#' ## Generic S3 method
#' csi(
#'  ...,
#'  micro = NULL,
#'  na.rm = TRUE
#' )
#' @export
csi <- function(
  ..., 
  micro = NULL, 
  na.rm = TRUE) {
  UseMethod(
    generic = "csi",
    object  = ..1
  )
}

#' @rdname jaccard
#' @usage
#' ## Generic S3 method
#' tscore(
#'  ...,
#'  micro = NULL,
#'  na.rm = TRUE
#' )
#' @export
tscore <- function(
  ...,
  micro = NULL, 
  na.rm = TRUE) {
  UseMethod(
    generic = "tscore",
    object  = ..1
  )
}

#' @rdname jaccard
#' @usage
#' ## Generic S3 method
#' weighted.jaccard(
#'  ...,
#'  w,
#'  micro = NULL,
#'  na.rm = TRUE
#' )
#' @export
weighted.jaccard <- function(
  ...,
  w,
  micro = NULL,
  na.rm = TRUE) {
  UseMethod(
    generic = "weighted.jaccard",
    object  = ..1
  )
}

#' @rdname jaccard
#' @usage
#' ## Generic S3 method
#' weighted.csi(
#'  ...,
#'  w,
#'  micro = NULL,
#'  na.rm = TRUE
#' )
#' @export
weighted.csi <- function(
  ...,
  w,
  micro = NULL,
  na.rm = TRUE) {
  UseMethod(
    generic = "weighted.csi",
    object  = ..1
  )
}

#' @rdname jaccard
#' @usage
#' ## Generic S3 method
#' weighted.tscore(
#'  ...,
#'  w,
#'  micro = NULL,
#'  na.rm = TRUE
#' )
#' @export
weighted.tscore <- function(
  ..., 
  w, 
  micro = NULL, 
  na.rm = TRUE) {
  UseMethod(
    generic = "weighted.tscore",
    object  = ..1
  )
}

# script end;
