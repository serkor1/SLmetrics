#' @title <%= tools::toTitleCase(.TITLE) %>
#' @rdname <%= .FUN %>
#' @name <%= .FUN %>
#' 
#' @description
#' 
#' A generic S3 function to compute the *<%= tolower(.TITLE) %>* score for a <%= tolower(.TASK) %> model. This function dispatches to S3 methods in \code{<%= .FUN %>()} and performs no input validation. If you supply [NA] values or vectors of unequal [length] (e.g. \code{length(x) != length(y)}), the underlying \code{C++} code may trigger undefined behavior and crash your \code{R} session.
#' 
<% if (.TYPE != "auc") { %>
#' ## Area under the curve
#' 
#' Use [auc.<%= .FUN %>] for calculating the area under the curve directly.
#' 
<% } else { %>
#' ## Visualizing <%= tolower(.TITLE) %>
#' 
#' Use [<%= gsub("weighted.auc.|auc.", "", .FUN) %>()] to construct the [data.frame] and use [plot] to visualize the area under the curve.
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
#' @keywords classification
#' @keywords evaluation
#' @concept Machine learning performance evaluation
#' 
<% if (.TYPE == "auc") { %>
#' @returns If `estimator` is given as
#' \itemize{
#'   \item 0: a named <[double]>-vector of [length] k
#'   \item 1: a <[double]> value (Micro averaged metric)
#'   \item 2: a <[double]> value (Macro averaged metric)
#' }
<% } %>
#' @references
#' 
#' James, Gareth, et al. An introduction to statistical learning. Vol. 112. No. 1. New York: springer, 2013.
#' 
#' Hastie, Trevor. "The elements of statistical learning: data mining, inference, and prediction." (2009).
#' 
#' Pedregosa, Fabian, et al. "Scikit-learn: Machine learning in Python." the Journal of machine Learning research 12 (2011): 2825-2830.
