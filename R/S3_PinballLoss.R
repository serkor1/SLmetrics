# script: Pinball Loss
# date: 2024-10-13
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate Methods
# script start;

#' @title Compute the \eqn{\text{pinball}} \eqn{\text{loss}}
#'
#' @description
#' The [pinball()]-function computes the [pinball loss](https://en.wikipedia.org/wiki/Quantile_regression) between
#' the observed and predicted <[numeric]> vectors. The [weighted.pinball()] function computes the weighted Pinball Loss.
#'
#' @inherit huberloss
#' @param alpha A <[numeric]>-value of [length] \eqn{1} (default: \eqn{0.5}). The slope of the pinball loss function.
#' @param deviance A <[logical]>-value of [length] 1 (default: [FALSE]). If [TRUE] the function returns the \eqn{D^2} loss.
#'
#' @example man/examples/scr_PinballLoss.R
#' @section Calculation:
#' 
#' The metric is calculated as,
#' 
#' \deqn{\text{PinballLoss}_{\text{unweighted}} = \frac{1}{n} \sum_{i=1}^{n} \left[ \alpha \cdot \max(0, y_i - \hat{y}_i) - (1 - \alpha) \cdot \max(0, \hat{y}_i - y_i) \right]}
#' 
#' where \eqn{y_i} is the actual value, \eqn{\hat{y}_i} is the predicted value and \eqn{\alpha} is the quantile level.
#'
#' @family Regression
#' @family Supervised Learning
#' @export
pinball <- function(...) {
  UseMethod(
    generic = "pinball",
    object  = ..1
  )
}

#' @rdname pinball
#' @export
weighted.pinball <- function(...) {
  UseMethod(
    generic = "weighted.pinball",
    object  = ..1
  )
}

# script end;
