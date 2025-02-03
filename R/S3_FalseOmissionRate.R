# script: False Omission Rate
# date: 2024-10-07
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate Method
# script start;

#' @inherit specificity
#' 
#' @title False Omission Rate
#' 
#' @description
#' A generic function for the [false omission rate](https://en.wikipedia.org/wiki/Positive_and_negative_predictive_values#False_omission_rate). Use [weighted.fdr()] for the weighted [false omission rate](https://en.wikipedia.org/wiki/Positive_and_negative_predictive_values#False_omission_rate).
#'
#' @section Definition:
#' Let \eqn{\hat{\beta} \in [0, 1]} be the proportion of false negatives among the predicted negatives. The false omission rate of the classifier is calculated as,
#'
#' \deqn{
#'   \hat{\beta} = \frac{\#FN_k}{\#TN_k + \#FN_k}
#' }
#'
#' Where:
#' 
#' - \eqn{\#TN_k} is the number of true negatives, and
#' - \eqn{\#FN_k} is the number of false negatives.
#'
#' @example man/examples/scr_FalseOmissionRate.R
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
