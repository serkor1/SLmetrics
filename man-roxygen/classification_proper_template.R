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
#' @inheritDotParams <%= .FUN %>.matrix
#' @inheritDotParams weighted.<%= .FUN %>.matrix
#' 
#' @returns 
#' A <[double]>-value 
#' 
#' @family Classification
#' @family Proper scoring rules
#' @family Supervised Learning
#' 
#' @examples
#' ## seed
#' set.seed(1903)
#' 
#' ## The general setup
#' ## with 3 classes
#' n_obs     <- 10
#' n_classes <- 3
#' 
#' ## Generate indicator matrix
#' ## with observed outcome (ok) and 
#' ## its predicted probability matrix (qk)
#' ok <- diag(n_classes)[ sample.int(n_classes, n_obs, TRUE), ]
#' qk <- matrix(runif(n_obs * n_classes), n_obs, n_classes)
#' qk <- qk / rowSums(qk)
#' 
#' ## Evaluate performance
#' SLmetrics::<%= .FUN %>(
#'    ok = ok, 
#'    qk = qk
#' )
#' 
#' @references
#' 
#' Gneiting, Tilmann, and Adrian E. Raftery. "Strictly proper scoring rules, prediction, and estimation." Journal of the American statistical Association 102.477 (2007): 359-378.
#' 
#' James, Gareth, et al. An introduction to statistical learning. Vol. 112. No. 1. New York: springer, 2013.
#' 
#' Hastie, Trevor. "The elements of statistical learning: data mining, inference, and prediction." (2009).
#' 
#' Pedregosa, Fabian, et al. "Scikit-learn: Machine learning in Python." the Journal of machine Learning research 12 (2011): 2825-2830.
