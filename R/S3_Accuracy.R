# script: Accuracy
# date: 2024-10-05
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate methods for accuracy
# script start;

#' @inherit specificity
#' 
#' @title Accuracy
#' 
#' @description
#' A generic function for the (normalized) [accuracy](https://developers.google.com/machine-learning/glossary#accuracy) in classification tasks. 
#' Use [weighted.accuracy()] for the weighted [accuracy](https://developers.google.com/machine-learning/glossary#accuracy).
#'
#' @usage
#' ## Generic S3 method
#' accuracy(...)
#' 
#' @param actual A vector of <[factor]> with [length] \eqn{n}, and \eqn{k} levels
#' @param predicted A vector of <[factor]> with [length] \eqn{n}, and \eqn{k} levels
#' @param w A <[numeric]>-vector of [length] \eqn{n}. [NULL] by default
#' @param x A confusion matrix created [cmatrix()]
#'
#' @section Definition:
#' Let \eqn{\hat{\alpha} \in [0, 1]} be the proportion of correctly predicted classes. The [accuracy](https://developers.google.com/machine-learning/glossary#accuracy) of the classifier is calculated as,
#'
#' \deqn{
#'   \hat{\alpha} = \frac{\#TP + \#TN}{\#TP + \#TN + \#FP + \#FN}
#' }
#' 
#' Where:
#' 
#' - \eqn{\#TP} is the number of true positives,
#' - \eqn{\#TN} is the number of true negatives,
#' - \eqn{\#FP} is the number of false positives, and
#' - \eqn{\#FN} is the number of false negatives.
#'
#' @returns
#' A <[numeric]>-vector of [length] 1
#'
#' @example man/examples/scr_Accuracy.R
#'
#' @family Classification
#' @family Supervised Learning
#' 
#' @export
accuracy <- function(...) {
  UseMethod(
    generic = "accuracy",
    object  = ..1
  )
}

#' @rdname accuracy
#' @usage
#' ## Generic S3 method
#' weighted.accuracy(
#' ...,
#' w
#' )
#' @export
weighted.accuracy <- function(
  ...,
  w) {
  UseMethod(
    generic = "weighted.accuracy",
    object  = ..1
  )
}

# script end;
