#' @title <%= tools::toTitleCase(.TITLE) %>
#' @rdname <%= .FUN %>
#' @name <%= .FUN %>
#' 
#' @keywords classification
#' @keywords evaluation
#' @concept Machine learning performance evaluation
#' 
#' @description
#' 
#' A generic S3 function to compute the *<%= tolower(.TITLE) %>* score for a <%= tolower(.TASK) %> model. This function dispatches to S3 methods in \code{<%= .FUN %>()} and performs no input validation. If you supply [NA] values or vectors of unequal [length] (e.g. \code{length(x) != length(y)}), the underlying \code{C++} code may trigger undefined behavior and crash your \code{R} session.
#' 
<% if (tolower(.TASK) == "classification") { %>
#' ## Efficient multi-metric evaluation
#' 
#' For multiple performance evaluations of a <%= tolower(.TASK) %> model, first compute the confusion matrix once via [cmatrix()]. All other performance metrics can then be derived from this one object via S3 dispatching:
#' 
#' ```r
#' ## compute confusion matrix
#' confusion_matrix <- cmatrix(actual, predicted)
#' 
#' ## evaluate <%= tolower(.TITLE) %>
#' ## via S3 dispatching
#' <%= .FUN %>(confusion_matrix)
#' 
#' ## additional performance metrics
#' ## below
#' ```
#' 
#' The [<%= .FUN %>.factor()] method calls [cmatrix()] internally, so explicitly invoking [<%= .FUN %>.cmatrix()] yourself avoids duplicate computation, yielding significant speed and memory effciency gains when you need multiple evaluation metrics.
#' 
#' 
#' 
<% } %>
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
#' @inheritDotParams <%= .FUN %>.factor
#' @inheritDotParams weighted.<%= .FUN %>.factor
#' @inheritDotParams <%= .FUN %>.cmatrix
#' 
#' 
<% if ( tolower(.MULTI_OUTPUT) == 'false' ) { %>
#' @returns 
#' A <[double]>-value 
<% } else { %>
#' @returns If `estimator` is given as
#' \itemize{
#'   \item 0 - a named <[double]> vector of [length] k
#'   \item 1 - a <[double]> value (Micro averaged metric)
#'   \item 2 - a <[double]> value (Macro averaged metric)
#' }
<% } %>
#' 
#' @family Classification
#' @family Supervised Learning
#' 
#' @examples
#' ## Classes and
#' ## seed
#' set.seed(1903)
#' classes <- c("Kebab", "Falafel")
#' 
#' ## Generate actual
#' ## and predicted classes
#' actual_classes <- factor(
#'     x = sample(x = classes, size = 10, replace = TRUE),
#'     levels = c("Kebab", "Falafel")
#' )
#' 
#' predicted_classes <- factor(
#'     x = sample(x = classes, size = 10, replace = TRUE),
#'     levels = c("Kebab", "Falafel")
#')
#' 
#' ## Evaluate performance
#' SLmetrics::<%= .FUN %>(
#'    actual_classes, 
#'    predicted_classes
#' )
#' 
#' @references
#' 
#' James, Gareth, et al. An introduction to statistical learning. Vol. 112. No. 1. New York: springer, 2013.
#' 
#' Hastie, Trevor. "The elements of statistical learning: data mining, inference, and prediction." (2009).
#' 
#' Pedregosa, Fabian, et al. "Scikit-learn: Machine learning in Python." the Journal of machine Learning research 12 (2011): 2825-2830.
