# script: False Omission Rate
# date: 2024-10-07
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate Method
# script start;

#' Compute the \eqn{\text{false}} \eqn{\text{omission}} \eqn{\text{rate}}
#'
#' @description
#' 
#' The [fer()]-function computes the [false omission rate](https://en.wikipedia.org/wiki/Positive_and_negative_predictive_values#False_omission_rate) (FOR), the proportion of false negatives among the predicted negatives, between
#' two vectors of predicted and observed [factor()] values.  The [weighted.fer()] function computes the weighted false omission rate.
#'
#' @example man/examples/scr_FalseOmissionRate.R
#' 
#' @inherit specificity
#'
#' @section Definition:
#'
#' The metric is calculated for each class \eqn{k} as follows,
#'
#' \deqn{
#'   \frac{\#FN_k}{\#FN_k + \#TN_k}
#' }
#'
#' Where \eqn{\#FN_k} and \eqn{\#TN_k} are the number of false negatives and true negatives, respectively, for each class \eqn{k}.
#'
#' @family Classification
#' @family Supervised Learning
#' 
#' @export
fer <- function(...) {
  UseMethod(
    generic = "fer",
    object  = ..1
  )
}

#' @rdname fer
#' @export
weighted.fer <- function(...) {
  UseMethod(
    generic = "weighted.fer",
    object  = ..1
  )
}

# script end;
