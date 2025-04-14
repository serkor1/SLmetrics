#' @title <%= tools::toTitleCase(.TITLE) %>
#' @rdname <%= .FUN %>
#' @name <%= .FUN %>
#' 
#' @examples
#' ## Generate actual
#' ## and predicted values
#' actual_values <- c(1.3, 0.4, 1.2, 1.4, 1.9, 1.0, 1.2)
#' 
#' predicted_values <- c(0.7, 0.5, 1.1, 1.2, 1.8, 1.1, 0.2)
#' 
#' ## Evaluate performance
#' SLmetrics::<%= .FUN %>(
#'    actual_values, 
#'    predicted_values
#' )
#' 
#' @description
#' A S3 generic function for calculating the <%= tolower(.TITLE) %> score of a regression model. [<%= .FUN %>()] handles the input as is - and therefore there is not sanity checks. 
#' If the data contains [NA], or `length(x) != length(y)` you are left at the mercy of compiler.
#' 
#' ## Defensive measures
#' 
#' As everything is based on pointers internally values as [NA] and out of bounds values (`length(x) != length(y)`) the compiler does not know how to react - this is undefined behaviour. And therefore it is not enough to wrap your call in `try()` or `tryCatch()` to recover from sudden errors. Your `R`-session *will* most likely just crash.
#' A workaroud is to create a wrapper around [<%= .FUN %>()] and any other evaluation metrics you are planning to use, and do the sanity checks before it reaches [<%= .FUN %>()].
#'
#' @usage
#' ## Generic S3 method
#' ## for <%= tools::toTitleCase(.TITLE) %>
#' <%= .FUN %>(...)
#' 
#' 
#' @returns 
#' A <[double]> value
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
#' 
#' @keywords regression
#' @keywords evaluation
#' @concept Machine learning performance evaluation
