#' @title <%= tools::toTitleCase(.TITLE) %>
#' @rdname <%= .FUN %>
#' @name <%= .FUN %>
#' 
#' @description
#' 
#' A generic S3 function to compute the *<%= tolower(.TITLE) %>* score for a <%= tolower(.TASK) %> model. This function dispatches to S3 methods in \code{<%= .FUN %>()} and performs no input validation. If you supply [NA] values or vectors of unequal [length] (e.g. \code{length(x) != length(y)}), the underlying \code{C++} code may trigger undefined behavior and crash your \code{R} session.
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
#' @keywords entropy
#' @keywords classification
#' @keywords evaluation
#' @concept Machine learning performance evaluation
#' 
#' @family Classification
#' @family Supervised Learning
#' 
<% if (grepl(pattern = "logloss", x = .FUN)) { %>
#' @returns 
#' A <[double]>
<% } else { %>
#' @returns A <[double]> value or vector:
#' - A single <[double]> value (length 1) if `dim == 0`.
#' - A <[double]> vector with length equal to the [length] of rows if `dim == 1`.
#' - A <[double]> vector with length equal to the [length] of columns if `dim == 2`.
<% } %>
#' 
#' @references
#' 
#' MacKay, David JC. Information theory, inference and learning algorithms. Cambridge university press, 2003.
#' 
#' Kramer, Oliver, and Oliver Kramer. "Scikit-learn." Machine learning for evolution strategies (2016): 45-53.
#' 
#' Virtanen, Pauli, et al. "SciPy 1.0: f'undamental algorithms for scientific computing in Python." Nature methods 17.3 (2020): 261-272.
