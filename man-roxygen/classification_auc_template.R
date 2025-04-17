#' @title <%= tools::toTitleCase(.TITLE) %>
#' @rdname <%= .FUN %>
#' @name <%= .FUN %>
#' 
#' @description
#' A S3 generic function for calculating the <%= tolower(.TITLE) %> score of a <%= tolower(.TASK) %> model. [<%= .FUN %>()] handles the input as is - and therefore there are no sanity checks. 
#' If the data contains [NA], or `length(x) != length(y)` you are left at the mercy of compiler.
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
#' As everything is based on pointers internally values as [NA] and out of bounds values (`length(x) != length(y)`) the compiler does not know how to react - this is undefined behaviour. And therefore it is not enough to wrap your call in `try()` or `tryCatch()` to recover from sudden errors. Your `R`-session *will* most likely just crash.
#' A workaround is to create a wrapper around [<%= .FUN %>()] and any other evaluation metrics you are planning to use, and do the sanity checks before it reaches [<%= .FUN %>()].
#' 
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
