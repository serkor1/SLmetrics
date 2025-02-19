# script: fbetascore
# date: 2024-10-01
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate methods
# script start;

#' @inherit specificity
#' 
#' @title \eqn{F_{\beta}}-score
#'
#' @description
#' A generic function for the [\eqn{F_{\beta}}](https://en.wikipedia.org/wiki/F1_score)-score. Use [weighted.fbeta()] for the weighted [\eqn{F_{\beta}}](https://en.wikipedia.org/wiki/F1_score)-score.
#' 
#' @usage
#' ## Generic S3 method
#' fbeta(
#'  ...,
#'  beta  = 1,
#'  micro = NULL,
#'  na.rm = TRUE
#' )
#' 
#' @param beta A <[numeric]> vector of [length] \eqn{1} (default: \eqn{1}).
#'
#' @section Definition:
#' Let \eqn{\hat{F}_{\beta} \in [0, 1]} be the \eqn{F_{\beta}} score, which is a weighted harmonic mean of precision and recall. \eqn{F_{\beta}} score of the classifier is calculated as,
#'
#' \deqn{
#'   \hat{F}_{\beta} = \left(1 + \beta^2\right) \frac{\text{Precision} \times \text{Recall}}
#'                                           {\beta^2 \times \text{Precision} + \text{Recall}}
#' }
#'
#' Substituting \eqn{\text{Precision} = \frac{\#TP_k}{\#TP_k + \#FP_k}} and \eqn{\text{Recall} = \frac{\#TP_k}{\#TP_k + \#FN_k}} yields:
#'
#' \deqn{
#'   \hat{F}_{\beta} = \left(1 + \beta^2\right)
#'     \frac{\frac{\#TP_k}{\#TP_k + \#FP_k} \times \frac{\#TP_k}{\#TP_k + \#FN_k}}
#'          {\beta^2 \times \frac{\#TP_k}{\#TP_k + \#FP_k} + \frac{\#TP_k}{\#TP_k + \#FN_k}}
#' }
#'
#' Where:
#' 
#' - \eqn{\#TP_k} is the number of true positives,
#' - \eqn{\#FP_k} is the number of false positives,
#' - \eqn{\#FN_k} is the number of false negatives, and
#' - \eqn{\beta} is a non-negative real number that determines the relative importance of precision vs. recall in the score.
#'
#' @example man/examples/scr_FBetaScore.R
#' 
#' @family Classification
#' @family Supervised Learning
#' 
#' @export
fbeta <- function(
  ...,
  beta  = 1,
  micro = NULL,
  na.rm = TRUE) {
  UseMethod(
    generic = "fbeta",
    object  = ..1
  )
}

#' @rdname fbeta
#' @usage
#' ## Generic S3 method
#' weighted.fbeta(
#'  ...,
#'  w,
#'  beta = 1,
#'  micro = NULL,
#'  na.rm = TRUE
#' )
#' @export
weighted.fbeta <- function(
  ...,
  w,
  beta  = 1,
  micro = NULL,
  na.rm = TRUE) {
  UseMethod(
    generic = "weighted.fbeta",
    object  = ..1
  )
}


# script end;
