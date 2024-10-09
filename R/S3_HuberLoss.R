# script: Huber Loss
# date: 2024-10-09
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate Methods
# script start;

#' Compute the \eqn{\text{huber}} \eqn{\text{loss}}
#'
#' @description
#' The [huberloss()]-function computes the simple and weighted [huber loss](https://en.wikipedia.org/wiki/Huber_loss) between
#' the predicted and observed <[numeric]> vectors.
#'
#'
#' @param actual A <[numeric]>-vector of [length] \eqn{n}. The observed (continuous) response variable.
#' @param predicted A <[numeric]>-vector of [length] \eqn{n}. The estimated (continuous) response variable.
#' @param w A <[numeric]>-vector of [length] \eqn{n}. The weight assigned to each observation in the data. See [stats::weighted.mean()] for more details.
#' @param delta A <[numeric]>-vector of [length] 1. 1 by default. The threshold value for switch between functions (see calculation).
#' @param ... Arguments passed into other methods.
#'
#' @section Calculation:
#'
#' The metric is calculated as follows,
#'
#' \deqn{
#'  \frac{1}{2} (y - \upsilon)^2 ~for~ |y - \upsilon| \leq \delta
#' }
#'
#' and
#'
#' \deqn{
#'   \delta |y-\upsilon|-\frac{1}{2} \delta^2 ~for~ \text{otherwise}
#' }
#'
#' where \eqn{y} and \eqn{\upsilon} are the `actual` and `predicted` values respectively. If `w` is not [NULL], then all values
#' are aggregated using the weights.
#'
#'
#' @example man/examples/scr_huberloss.R
#'
#'
#' @family regression
#'
#' @returns A <[numeric]> vector of [length] 1.
#'
#' @export
huberloss <- function(...) {
  UseMethod(
    generic = "huberloss",
    object  = ..1
  )
}

# script end;
