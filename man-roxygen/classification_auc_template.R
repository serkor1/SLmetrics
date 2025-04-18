#' @inheritDotParams <%= .FUN %>.factor
#' @inheritDotParams weighted.<%= .FUN %>.factor
#' 
#' @description
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
#' 
<% if (.TYPE == "auc") { %>
#' @returns If `estimator` is given as
#' \itemize{
#'   \item 0: a named <[double]>-vector of [length] k
#'   \item 1: a <[double]> value (Micro averaged metric)
#'   \item 2: a <[double]> value (Macro averaged metric)
#' }
<% } %>
#'
#' 
#' @references
#' 
#' James, Gareth, et al. An introduction to statistical learning. Vol. 112. No. 1. New York: springer, 2013.
#' 
#' Hastie, Trevor. "The elements of statistical learning: data mining, inference, and prediction." (2009).
#' 
#' Pedregosa, Fabian, et al. "Scikit-learn: Machine learning in Python." the Journal of machine Learning research 12 (2011): 2825-2830.
#' 
#' @family Classification
#' @family Supervised Learning
