<% 
if (!exists(".SINGLE_OUTPUT", inherits = FALSE)) {
  .SINGLE_OUTPUT <- FALSE
}
value = as.logical(.SINGLE_OUTPUT)
%>
#' @title <%= tools::toTitleCase(.TITLE) %>
#' @rdname <%= .FUN %>
#' @name <%= .FUN %>
#' 
#' @keywords classification
#' @keywords evaluation
#' @concept Machine learning performance evaluation
#' 
#' @description
#' A S3 generic function for calculating the <%= tolower(.TITLE) %> score of a <%= tolower(.TASK) %> model. [<%= .FUN %>()] handles the input as is - and therefore there is not sanity checks. 
#' If the data contains [NA], or `length(x) != length(y)` you are left at the mercy of compiler.
#' 
<% if (tolower(.TASK) == "classification") { %>
#' ## Efficient evaluation
#' 
#' The canonical way of measuring the performance of a <%= tolower(.TASK) %> model is to use the [<%= .FUN %>.cmatrix()]-method. [<%= .FUN %>.factor()] calls [cmatrix()] internally, and for multiple measures there is significant speed and memory efficiency gain in constructing the confusion matrix first.
#' 
<% } %>
#'
#' ## Defensive measures
#' 
#' As everything is based on pointers internally values as [NA] and out of bounds values (`length(x) != length(y)`) the compiler does not know how to react - this is undefined behaviour. And therefore it is not enough to wrap your call in `try()` or `tryCatch()` to recover from sudden errors. Your `R`-session *will* most likely just crash.
#' A workaroud is to create a wrapper around [<%= .FUN %>()] and any other evaluation metrics you are planning to use, and do the sanity checks before it reaches [<%= .FUN %>()].
#'
#' 
#' @returns 
<% if (value) { %>
#' A <[double]>-value 
<% } else { %>
#' @returns If `estimator` is given as
#' \itemize{
#'   \item 0 - a named <[numeric]>-vector of [length] k
#'   \item 1 - a <[double]> value (Micro averaged metric)
#'   \item 2 - a <[double]> value (Macro averaged metric)
#' }
<% } %>
#'
#' @references
#' 
#' James, Gareth, et al. An introduction to statistical learning. Vol. 112. No. 1. New York: springer, 2013.
#' 
#' Hastie, Trevor. "The elements of statistical learning: data mining, inference, and prediction." (2009).
#' 
#' Virtanen, Pauli, et al. "SciPy 1.0: fundamental algorithms for scientific computing in Python." Nature methods 17.3 (2020): 261-272.
