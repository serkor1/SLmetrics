# script: Pinball Loss
# date: 2024-10-13
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate Methods
# script start;

#' @title Compute the \eqn{\text{pinball}} \eqn{\text{loss}}
#'
#' @description
#' The [pinball()]-function computes the [pinball loss](https://en.wikipedia.org/wiki/Quantile_regression) between
#' the observed and predicted <[numeric]> vectors. If If `w` is not [NULL], the function returns the weighted pinball loss.
#'
#' @inherit huberloss
#' @param alpha A <[numeric]>-value of [length] 1. The slope of the pinball loss function. \eqn{0.5} by default.
#' @param deviance A <[logical]>-value of [length] 1. [FALSE] by default. If [TRUE] the function returns the \eqn{D^2} loss.
#'
#' @example man/examples/scr_pinball.R
#' @section Calculation:
#' 
#' The pinball loss measures the accuracy of quantile predictions by penalizing overestimates and underestimates asymmetrically based on the specified quantile (\code{alpha}).
#' 
#' **Weighted Pinball Loss**:
#' \deqn{\text{PinballLoss}_{\text{weighted}} = \frac{\sum_{i=1}^{n} w_i \cdot \left[ \alpha \cdot \max(0, y_i - \hat{y}_i) - (1 - \alpha) \cdot \max(0, \hat{y}_i - y_i) \right]}{\sum_{i=1}^{n} w_i}}
#' where:
#' \itemize{
#'   \item \eqn{y_i} is the actual value,
#'   \item \eqn{\hat{y}_i} is the predicted value,
#'   \item \eqn{w_i} is the weight for observation \eqn{i},
#'   \item \eqn{\alpha} is the quantile level.
#' }
#' 
#' **Unweighted Pinball Loss**:
#' \deqn{\text{PinballLoss}_{\text{unweighted}} = \frac{1}{n} \sum_{i=1}^{n} \left[ \alpha \cdot \max(0, y_i - \hat{y}_i) - (1 - \alpha) \cdot \max(0, \hat{y}_i - y_i) \right]}
#' where:
#' \itemize{
#'   \item \eqn{y_i} is the actual value,
#'   \item \eqn{\hat{y}_i} is the predicted value,
#'   \item \eqn{\alpha} is the quantile level.
#' }
#'
#' @family regression
#' @export
pinball <- function(...) {
  UseMethod(
    generic = "pinball",
    object  = ..1
  )
}

# script end;
