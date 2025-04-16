#' @title <%= tools::toTitleCase(.TITLE) %>
#' @rdname <%= .FUN %>
#' @name <%= .FUN %>
#' 
#' @keywords classification
#' @keywords evaluation
#' @concept Machine learning performance evaluation
#' 
#' @description
#' A S3 generic function for calculating the <%= tolower(.TITLE) %> of a <%= tolower(.TASK) %> model. [<%= .FUN %>()] handles the input as is - and therefore there is not sanity checks. 
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
#' @inheritDotParams <%= .FUN %>.numeric
#' @inheritDotParams weighted.<%= .FUN %>.numeric
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
#' ## Generate actual (p)
#' ## and predicted (q) probabilities
#' p <- runif(n = 1e2)
#' q <- runif(n = 1e2)
#' 
#' ## Evaluate performance
#' SLmetrics::<%= .FUN %>(
#'    p = p, 
#'    q = q
#' )
#' 
#' @references
#' 
#' James, Gareth, et al. An introduction to statistical learning. Vol. 112. No. 1. New York: springer, 2013.
#' 
#' Hastie, Trevor. "The elements of statistical learning: data mining, inference, and prediction." (2009).
#' 
#' Pedregosa, Fabian, et al. "Scikit-learn: Machine learning in Python." the Journal of machine Learning research 12 (2011): 2825-2830.
