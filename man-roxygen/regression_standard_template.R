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
#' 
#' A generic S3 function to compute the *<%= tolower(.TITLE) %>* score for a regression model. This function dispatches to S3 methods in \code{<%= .FUN %>()} and performs no input validation. If you supply [NA] values or vectors of unequal [length] (e.g. \code{length(x) != length(y)}), the underlying \code{C++} code may trigger undefined behavior and crash your \code{R} session.
#' 
#' ## Defensive measures
#'
#' Because [<%= .FUN %>()] operates on raw pointers, pointer‑level faults (e.g. from [NA] or mismatched [length]) occur before any \code{R}‑level error handling.  Wrapping calls in [try()] or [tryCatch()] will *not* prevent \code{R}-session crashes.
#' 
#' To guard against this, wrap [<%= .FUN %>()] in a “safe” validator that checks for [NA] values and matching [length], for example:
#'
#' ```r
#' safe_<%= .FUN %> <- function(x, y, ...) {
#'   stopifnot(
#'     !anyNA(x), !anyNA(y),
#'     length(x) == length(y)
#'   )
#'   <%= .FUN %>(x, y, ...)
#' }
#' ```
#' Apply the same pattern to any custom metric functions to ensure input sanity before calling the underlying \code{C++} code.
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
