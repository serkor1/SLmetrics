# script: Balanced Accuracy
# date: 2024-12-18
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate methods for balanced accuracy
# script start;

#' Compute the \eqn{\text{balanced}} \eqn{\text{accuracy}}
#'
#' The [baccuracy()]-function computes the [balanced accuracy](https://neptune.ai/blog/balanced-accuracy) between two
#' vectors of predicted and observed [factor()] values. The [weighted.baccuracy()] function computes the weighted balanced accuracy.
#'
#'
#' @inherit accuracy
#' @param adjust A [logical] value (default: [FALSE]). If [TRUE] the metric is adjusted for random chance \eqn{\frac{1}{k}}.
#' @param na.rm A [logical] values (default: [TRUE]).  If [TRUE] calculation of the metric is based on valid classes.
#'
#' @section Calculation:
#'
#' The metric is calculated as follows,
#'
#' \deqn{
#'   \frac{\text{sensitivity} + \text{specificty}}{2}
#' }
#'
#' See the [sensitivity()]- and/or [specificity()]-function for more details.
#'
#' @returns
#'
#' A [numeric]-vector of [length] 1
#'
#' @example man/examples/scr_BalancedAccuracy.R
#'
#' @family Classification
#' @family Supervised Learning
#'
#' @export
baccuracy <- function(...) {
  UseMethod(
    generic = "baccuracy",
    object  = ..1
  )
}

#' @rdname baccuracy
#' @export
weighted.baccuracy <- function(...) {
  UseMethod(
    generic = "weighted.baccuracy",
    object  = ..1
  )
}

# script end;