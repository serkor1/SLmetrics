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
jaccard <- function(...) {
  UseMethod(
    generic = "jaccard",
    object  = ..1
  )
}

#' @rdname jaccard
#' @export
csi <- function(...) {
  UseMethod(
    generic = "csi",
    object  = ..1
  )
}

#' @rdname jaccard
#' @export
tscore <- function(...) {
  UseMethod(
    generic = "tscore",
    object  = ..1
  )
}

#' @rdname jaccard
#' @export
weighted.jaccard <- function(...) {
  UseMethod(
    generic = "weighted.jaccard",
    object  = ..1
  )
}

#' @rdname jaccard
#' @export
weighted.csi <- function(...) {
  UseMethod(
    generic = "weighted.csi",
    object  = ..1
  )
}

#' @rdname jaccard
#' @export
weighted.tscore <- function(...) {
  UseMethod(
    generic = "weighted.tscore",
    object  = ..1
  )
}

# script end;
