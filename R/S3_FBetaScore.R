# script: fbetascore
# date: 2024-10-01
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate methods
# script start;



#' Compute the \eqn{F_{\beta}}-score
#'
#' @description
#' The [fbeta()]-function computes the [\eqn{F_\beta} score](https://en.wikipedia.org/wiki/F1_score), the weighted harmonic mean of [precision()] and [recall()], between
#' two vectors of predicted and observed [factor()] values. The parameter \eqn{\beta} determines the weight of precision and recall in the combined score.
#'
#' When `aggregate = TRUE`, the function returns the micro-average \eqn{F_\beta} score across all classes \eqn{k}. By default, it returns the class-wise \eqn{F_\beta} score.
#'
#'
#' @example man/examples/scr_FBetaScore.R
#'
#' @inherit specificity
#' @param beta A <[numeric]> vector of length 1. 1 by default, see calculations.
#'
#' @section Calculation:
#'
#' The metric is calculated for each class \eqn{k} as follows,
#'
#'
#' \deqn{
#'   (1 + \beta^2) \frac{\text{Precision}_k \cdot \text{Recall}_k}{(\beta^2 \cdot \text{Precision}_k) + \text{Recall}_k}
#' }
#'
#' Where precision is \eqn{\frac{\#TP_k}{\#TP_k + \#FP_k}} and recall (sensitivity) is \eqn{\frac{\#TP_k}{\#TP_k + \#FN_k}}, and \eqn{\beta} determines the weight of precision relative to recall.
#'
#' When `aggregate = TRUE`, the `micro`-average \eqn{F_\beta} score is calculated,
#'
#' \deqn{
#'   (1 + \beta^2) \frac{\sum_{k=1}^K \text{Precision}_k \cdot \sum_{k=1}^K \text{Recall}_k}{(\beta^2 \cdot \sum_{k=1}^K \text{Precision}_k) + \sum_{k=1}^K \text{Recall}_k}
#' }
#'
#'
#' @family classification
#' @export
fbeta <- function(...) {
  UseMethod(
    generic = "fbeta",
    object  = ..1
  )
}

#' @rdname fbeta
#' @export
weighted.fbeta <- function(...) {
  UseMethod(
    generic = "weighted.fbeta",
    object  = ..1
  )
}


# script end;
