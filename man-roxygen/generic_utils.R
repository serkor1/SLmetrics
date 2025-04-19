#' @rdname utils_<%= .FUN %>
#' @name <%= .FUN %>
#' 
#' @title <%= tools::toTitleCase(.TITLE) %>
#' 
#' @description
#' A generic S3 function for <%= tolower(.OBJECTIVE) %>. This function dispatches to S3 methods in [<%= .FUN %>()] and performs no input validation. If you supply [NA] values or vectors of unequal [length] (e.g. \code{length(x) != length(y)}), the underlying \code{C++} code may trigger undefined behavior and crash your \code{R} session.
#' 
<% if (grepl(pattern = "true", x = .DEFENSE)) { %>
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
#' 
<% } %>
#' 
#' @param ... Arguments passed into other methods
#'
#' 
#' 
#' @usage
#' ## Generic S3 method
#' ## for <%= tools::toTitleCase(.TITLE) %>
#' <%= .FUN %>(...)
#' 
#' 
#' @family Utilities
