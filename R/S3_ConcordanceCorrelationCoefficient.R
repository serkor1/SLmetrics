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
#' A generic function for the [concordance correlation coefficient](https://en.wikipedia.org/wiki/Concordance_correlation_coefficient). Use [weighted.ccc()] for the weighted [concordance correlation coefficient](https://en.wikipedia.org/wiki/Concordance_correlation_coefficient).
#' 
#' 
#' @param correction A <[logical]> vector of [length] \eqn{1} (default: [FALSE]). If [TRUE] the variance and covariance
#' will be adjusted with \eqn{\frac{1-n}{n}}
#' 
#' @section Definition:
#' Let \eqn{\rho_c \in [0,1]} measure the agreement between \eqn{y} and \eqn{\upsilon}. The classifier agreement is calculated as, 
#' 
#' \deqn{
#'   \rho_c = \frac{2 \rho \sigma_{\upsilon} \sigma_y}{\sigma_{\upsilon}^2 + \sigma_y^2 + (\mu_{\upsilon} - \mu_y)^2}
#' }
#'
#' Where:
#' - \eqn{\rho} is the pearson correlation coefficient
#' - \eqn{\sigma_y} is the unbiased standard deviation of \eqn{y}
#' - \eqn{\sigma_{\upsilon}} is the unbiased standard deviation of \eqn{\upsilon}
#' - \eqn{\mu_y} is the mean of \eqn{y}
#' - \eqn{\mu_{\upsilon}} is the mean of \eqn{\upsilon}
#' 
#' If `correction == TRUE` each \eqn{\sigma_{i \in [y, \upsilon]}} is adjusted by \eqn{\frac{1-n}{n}}
#' 
#' @example man/examples/scr_ConcordanceCorrelationCoefficient.R
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
