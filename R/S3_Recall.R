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
