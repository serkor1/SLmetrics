#' @inheritDotParams <%= .FUN %>.numeric
#' @inheritDotParams weighted.<%= .FUN %>.numeric
#' 
#' @returns 
#' A <[double]> value
#' 
#' @examples
#' ## Generate actual
#' ## and predicted values
#' actual_values    <- c(1.3, 0.4, 1.2, 1.4, 1.9, 1.0, 1.2)
#' predicted_values <- c(0.7, 0.5, 1.1, 1.2, 1.8, 1.1, 0.2)
#' 
#' ## Evaluate performance
#' SLmetrics::<%= .FUN %>(
#'    actual    = actual_values, 
#'    predicted = predicted_values
#' )
#'
#' @references
#' 
#' James, Gareth, et al. An introduction to statistical learning. Vol. 112. No. 1. New York: springer, 2013.
#' 
#' Hastie, Trevor. "The elements of statistical learning: data mining, inference, and prediction." (2009).
#' 
#' Virtanen, Pauli, et al. "SciPy 1.0: fundamental algorithms for scientific computing in Python." Nature methods 17.3 (2020): 261-272.
#' 
#' @family Regression
#' @family Supervised Learning
