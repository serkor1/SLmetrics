# script: Concordance Correlation Coefficient
# date: 2024-10-10
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate Methods
# script start;

#' @inherit huberloss
#' 
#' @title Concordance Correlation Coefficient
#'
#' @description
#' The [ccc()]-function computes the simple and weighted [concordance correlation coefficient](https://en.wikipedia.org/wiki/Concordance_correlation_coefficient) between
#' the two vectors of predicted and observed <[numeric]> values.  The [weighted.ccc()] function computes the weighted Concordance Correlation Coefficient. 
#' If `correction` is [TRUE] \eqn{\sigma^2} is adjusted by \eqn{\frac{1-n}{n}} in the intermediate steps.
#' 
#' @param correction A <[logical]> vector of [length] \eqn{1} (default: [FALSE]). If [TRUE] the variance and covariance
#' will be adjusted with \eqn{\frac{1-n}{n}}
#'
#' @example man/examples/scr_ConcordanceCorrelationCoefficient.R
#'
#' @section Definition:
#'
#' The metric is calculated as follows,
#'
#' \deqn{
#'   \rho_c = \frac{2 \rho \sigma_x \sigma_y}{\sigma_x^2 + \sigma_y^2 + (\mu_x - \mu_y)^2}
#' }
#'
#' Where \eqn{\rho} is the \eqn{\text{pearson correlation coefficient}}, \eqn{\sigma} is the \eqn{\text{standard deviation}} and \eqn{\mu} is the simple mean of `actual` and `predicted`.
#' 
#'
#' @family Regression
#' @family Supervised Learning
#' 
#' @export
ccc <- function(...) {
  UseMethod(
    generic = "ccc",
    object  = ..1
  )
}

#' @rdname ccc
#' @export
weighted.ccc <- function(...) {
  UseMethod(
    generic = "weighted.ccc",
    object  = ..1
  )
}
# script end;
