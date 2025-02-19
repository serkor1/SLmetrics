# script: Fowlkes Mallows Index
# date: 2024-10-07
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate methods
# script start;

#' @inherit accuracy
#' 
#' @title Fowlkes-Mallows Index
#'
#' @description
#' The [fmi()]-function computes the [Fowlkes-Mallows Index](https://en.wikipedia.org/wiki/Fowlkes%E2%80%93Mallows_index) (FMI), a measure of the similarity between two sets of clusterings, between
#' two vectors of predicted and observed [factor()] values.
#' 
#' @usage
#' ## Generic S3 method
#' fmi(...)
#' 
#' @section Definition:
#'
#' The metric is calculated for each class \eqn{k} as follows,
#'
#' \deqn{
#'   \sqrt{\frac{\#TP_k}{\#TP_k + \#FP_k} \times \frac{\#TP_k}{\#TP_k + \#FN_k}}
#' }
#'
#' Where \eqn{\#TP_k}, \eqn{\#FP_k}, and \eqn{\#FN_k} represent the number of true positives, false positives, and false negatives for each class \eqn{k}, respectively.
#' 
#' @example man/examples/scr_FowlkesMallowsIndex.R
#'
#' @family Classification
#' @family Unsupervised Learning
#' 
#' @export
fmi <- function(...) {
  UseMethod(
    generic = "fmi",
    object  = ..1 
  )
}

# script end;
