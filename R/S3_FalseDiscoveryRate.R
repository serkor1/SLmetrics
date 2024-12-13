# script: False Discovery Rate
# date: 2024-10-07
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate Methods
# script start;

#' Compute the \eqn{\text{false}} \eqn{\text{discovery}} \eqn{\text{rate}}
#'
#' @description
#' The [fdr()]-function computes the [false discovery rate](https://en.wikipedia.org/wiki/False_discovery_rate) (FDR), the proportion of false positives among the predicted positives, between
#' two vectors of predicted and observed [factor()] values.
#'
#' When `aggregate = TRUE`, the function returns the micro-average FDR across all classes \eqn{k}. By default, it returns the class-wise FDR.
#'
#' @example man/examples/scr_fdr.R
#'
#' @inherit specificity
#'
#' @section Calculation:
#'
#' The metric is calculated for each class \eqn{k} as follows,
#'
#' \deqn{
#'   \frac{\#FP_k}{\#TP_k+\#FP_k}
#' }
#'
#' Where \eqn{\#TP_k} and \eqn{\#FP_k} is the number of true psotives and false positives, respectively, for each class \eqn{k}.
#'
#' When `aggregate = TRUE` the `micro`-average is calculated,
#'
#' \deqn{
#'  \frac{\sum_{k=1}^k \#FP_k}{\sum_{k=1}^k \#TP_k + \sum_{k=1}^k \#FP_k}
#' }
#'
#' @family classification
#' @export
fdr <- function(...) {
  UseMethod(
    generic = "fdr",
    object   = ..1
  )
}

# script end;
