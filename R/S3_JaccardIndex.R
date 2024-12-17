# script: Jaccard Methods
# date: 2024-10-06
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Create Methods
# script start;

#' Compute the \eqn{\text{Jaccard}} \eqn{\text{index}}
#'
#' @description
#' The [jaccard()]-function computes the [Jaccard Index](https://en.wikipedia.org/wiki/Jaccard_index), also known as the Intersection over Union, between
#' two vectors of predicted and observed [factor()] values.
#'
#' When `aggregate = TRUE`, the function returns the micro-average Jaccard Index across all classes \eqn{k}.
#' By default, it returns the class-wise Jaccard Index.
#'
#' @inherit specificity
#'
#' @section Calculation:
#'
#' The metric is calculated for each class \eqn{k} as follows,
#'
#' \deqn{
#'   \frac{\#TP_k}{\#TP_k + \#FP_k + \#FN_k}
#' }
#'
#' Where \eqn{\#TP_k}, \eqn{\#FP_k}, and \eqn{\#FN_k} represent the number of true positives, false positives, and false negatives for each class \eqn{k}, respectively.
#'
#' When `aggregate = TRUE`, the micro-average is calculated as,
#'
#' \deqn{
#'   \frac{\sum_{i = 1}^{k} TP_i}{\sum_{i = 1}^{k} TP_i + \sum_{i = 1}^{k} FP_k + \sum_{i = 1}^{k} FN_k}
#' }
#'
#' @example man/examples/scr_jaccard.R
#'
#' @family classification
#'
#' @aliases jaccard csi tscore
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
