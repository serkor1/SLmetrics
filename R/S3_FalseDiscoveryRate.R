# script: False Discovery Rate
# date: 2024-10-07
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate Methods
# script start;

#' @inherit specificity
#' 
#' @title false discovery rate
#'
#' @description
#' 
#' The [fdr()]-function computes the [false discovery rate](https://en.wikipedia.org/wiki/False_discovery_rate) (FDR), the proportion of false positives among the predicted positives, between
#' two vectors of predicted and observed [factor()] values. The [weighted.fdr()] function computes the weighted false discovery rate.
#'
#' @example man/examples/scr_FalseDiscoveryRate.R

#' @section Definition:
#'
#' The metric is calculated for each class \eqn{k} as follows,
#'
#' \deqn{
#'   \frac{\#FP_k}{\#TP_k+\#FP_k}
#' }
#'
#' Where \eqn{\#TP_k} and \eqn{\#FP_k} is the number of true psotives and false positives, respectively, for each class \eqn{k}.
#' 
#' @family Classification
#' @family Supervised Learning
#' 
#' @export
fdr <- function(...) {
  UseMethod(
    generic = "fdr",
    object   = ..1
  )
}

#' @rdname fdr
#' @export
weighted.fdr <- function(...) {
  UseMethod(
    generic = "weighted.fdr",
    object   = ..1
  )
}

# script end;
