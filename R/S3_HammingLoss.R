# script: Hamming Loss
# date: 2025-08-04
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate Methods
# script start;

#' @inherit accuracy
#'
#' @title Hamming Loss
#'
#' @description
#' A generic function for the [Hamming  loss](https://en.wikipedia.org/wiki/Hamming_distance) in classification tasks. Use [weighted.hammingloss()] for the weighted [Hamming  loss](https://en.wikipedia.org/wiki/Hamming_distance).
#' 
#' @usage
#' ## Generic S3 method
#' hammingloss(...)
#' 
#' @section Definition:
#' Let \eqn{L_{Hamming} \in [0, 1]} be the Hamming loss, which measures the fraction of incorrectly predicted labels. The Hamming loss of a classifier is calculated as,
#'
#' \deqn{
#' L_{Hamming} = \frac{1}{N \times L} \sum_{i=1}^{N} \sum_{j=1}^{L} \mathbf{1}(\hat{y}{ij} \neq y{ij})
#' }
#'
#' Where:
#'
#' - \eqn{N} is the number of samples,
#' - \eqn{L} is the number of labels,
#' - \eqn{\hat{y}{ij}} is the predicted value of the \eqn{j}-th label for the \eqn{i}-th sample,
#' - \eqn{y{ij}} is the true value of the \eqn{j}-th label for the \eqn{i}-th sample, and
#' - \eqn{\mathbf{1}(\cdot)} is the indicator function that returns 1 if the argument is true and 0 otherwise.
#'
#' For binary classification tasks, the Hamming loss can be expressed in terms of standard binary classification metrics:
#'
#' \deqn{
#' L_{Hamming} = \frac{#FP + #FN}{#TP + #TN + #FP + #FN}
#' }
#'
#' Where:
#'
#' - \eqn{#TP} is the number of true positives,
#' - \eqn{#TN} is the number of true negatives,
#' - \eqn{#FP} is the number of false positives, and
#' - \eqn{#FN} is the number of false negatives.
#'
#' The Hamming loss ranges from 0 to 1, where 0 represents perfect prediction (no errors) and 1 represents the worst possible prediction (all errors). A smaller Hamming loss indicates better classification performance.
#'
#' @example man/examples/scr_HammingLoss.R
#'
#' @family Classification
#' @family Supervised Learning
#'
#' @export
hammingloss <- function(...) {
  UseMethod(
    generic = "hammingloss",
    object  = ..1
  )
}

#' @rdname hammingloss
#' @usage
#' ## Generic S3 method
#' weighted.hammingloss(
#'  ...,
#'  w
#' )
#' @export
weighted.hammingloss <- function(
  ...,
  w) {
  UseMethod(
    generic = "weighted.hammingloss",
    object  = ..1
  )
}

# script end;
