# script: precision
# date: 2024-10-01
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate method
# script start;


#' Compute the \eqn{\text{precision}} or  \eqn{\text{positive predictive value}}
#'
#' @description
#' The [precision()]-function computes the [precision](https://en.wikipedia.org/wiki/Positive_and_negative_predictive_values), also known as the positive predictive value (PPV), between
#' two vectors of predicted and observed [factor()] values.
#'
#' When `aggregate = TRUE`, the function returns the micro-average precision across all classes \eqn{k}.
#' By default, it returns the class-wise precision.
#'
#' @inherit specificity
#'
#' @section Calculation:
#'
#' The metric is calculated for each class \eqn{k} as follows,
#'
#' \deqn{
#'   \frac{\#TP_k}{\#TP_k + \#FP_k}
#' }
#'
#' Where \eqn{\#TP_k} and \eqn{\#FP_k} are the number of true positives and false positives, respectively, for each class \eqn{k}.
#'
#' When `aggregate = TRUE`, the `micro`-average is calculated,
#'
#' \deqn{
#'   \frac{\sum_{k=1}^k \#TP_k}{\sum_{k=1}^k \#TP_k + \sum_{k=1}^k \#FP_k}
#' }
#'
#' @example man/examples/scr_precision.R
#'
#' @family classification
#'
#' @aliases precision ppv
#'
#' @export
precision <- function(...) {
  UseMethod(
    generic = "precision",
    object  = ..1
  )
}

#' @rdname precision
#' @export
ppv <- function(...) {
  UseMethod(
    generic = "ppv",
    object  = ..1
  )
}

# script end;
