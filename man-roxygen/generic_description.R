#' @rdname <%= tolower(.TASK) %>_<%= .FUN %>
#' @name <%= .FUN %>
#' 
#' @concept Performance evaluation
#' @concept Statistical learning
#' @concept Machine learning
#' 
#' @keywords classification
#' @keywords regression
#' @keywords evaluation
#' 
#' @title <%= tools::toTitleCase(.TITLE) %>
#' 
#' @description
#' 
#' A generic S3 function to compute the *<%= tolower(.TITLE) %>* <%= if (grepl(pattern = "cmatrix", x = .FUN)) "" else "score" %> for a <%= tolower(.TASK) %> model. This function dispatches to S3 methods in [<%= .FUN %>()] and performs no input validation. If you supply [NA] values or vectors of unequal [length] (e.g. \code{length(x) != length(y)}), the underlying \code{C++} code may trigger undefined behavior and crash your \code{R} session.
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
#'
#' @usage
#' ## Generic S3 method
#' ## for <%= tools::toTitleCase(.TITLE) %>
#' <%= .FUN %>(...)
