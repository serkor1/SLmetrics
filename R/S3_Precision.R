# script: precision
# date: 2024-10-01
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate method
# script start;


#' Compute the \eqn{\text{precision}} or \eqn{\text{positive}} \eqn{\text{predictive}} \eqn{\text{value}}
#'
#' @description
#' The [precision()]-function computes the [precision](https://en.wikipedia.org/wiki/Positive_and_negative_predictive_values), also known as the positive predictive value (PPV), between
#' two vectors of predicted and observed [factor()] values. The [weighted.precision()] function computes the weighted precision.
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
#' @example man/examples/scr_Precision.R
#'
#' @family Classification
#' @family Supervised Learning
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
weighted.precision <- function(...) {
  UseMethod(
    generic = "weighted.precision",
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

#' @rdname precision
#' @export
weighted.ppv <- function(...) {
  UseMethod(
    generic = "weighted.ppv",
    object  = ..1
  )
}

# script end;
