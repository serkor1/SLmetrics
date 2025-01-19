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
#' The [recall()]-function computes the [recall](https://en.wikipedia.org/wiki/Sensitivity_and_specificity), also known as sensitivity or the True Positive Rate (TPR), between
#' two vectors of predicted and observed [factor()] values. The [weighted.recall()] function computes the weighted recall.
#' 
#' ## Other names
#' Sensitivity, True Positive Rate
#' 
#' @section Definition:
#'
#' The metric is calculated for each class \eqn{k} as follows,
#'
#' \deqn{
#'   \frac{\#TP_k}{\#TP_k + \#FN_k}
#' }
#'
#' Where \eqn{\#TP_k} and \eqn{\#FN_k} is the number of true positives and false negatives, respectively, for each class \eqn{k}.
#' 
#' @example man/examples/scr_Recall.R
#'
#' @family Classification
#' @family Supervised Learning
#' 
#' @export
recall <- function(...) {
  UseMethod(
    generic = "recall",
    object  = ..1
  )
}

#' @rdname recall
#' @export
sensitivity <- function(...) {
  UseMethod(
    generic = "sensitivity",
    object  = ..1
  )
}

#' @rdname recall
#' @export
tpr <- function(...) {
  UseMethod(
    generic = "tpr",
    object  = ..1
  )
}


#' @rdname recall
#' @export
weighted.recall <- function(...) {
  UseMethod(
    generic = "weighted.recall",
    object  = ..1
  )
}

#' @rdname recall
#' @export
weighted.sensitivity <- function(...) {
  UseMethod(
    generic = "weighted.sensitivity",
    object  = ..1
  )
}

#' @rdname recall
#' @export
weighted.tpr <- function(...) {
  UseMethod(
    generic = "weighted.tpr",
    object  = ..1
  )
}

# script end;
