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
#' ## Efficient multi-metric evaluation
#' 
#' To avoid sorting the same probability matrix multiple times (once per class or curve), you can precompute a single set of sort indices and pass it via the `indices` argument. This reduces the overall cost from O(K·N log N) to O(N log N + K·N).
#' 
#' ```r
#' ## presort response
#' ## probabilities
#' indices <- preorder(response, decreasing = TRUE)
#' 
#' ## evaluate <%= tolower(.TITLE) %>
#' <%= .FUN %>(actual, response, indices = indices)
#' ```
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
#' @examples
#' ## Classes and
#' ## seed
#' set.seed(1903)
#' classes <- c("Kebab", "Falafel")
#' 
#' ## Generate actual classes
#' ## and response probabilities
#' actual_classes <- factor(
#'     x = sample(
#'       x = classes, 
#'       size = 1e2, 
#'       replace = TRUE, 
#'       prob = c(0.7, 0.3)
#'     )
#' )
#' 
#' response_probabilities <- ifelse(
#'     actual_classes == "Kebab", 
#'     rbeta(sum(actual_classes == "Kebab"), 2, 5), 
#'     rbeta(sum(actual_classes == "Falafel"), 5, 2)
#' )
#' 
#' ## Construct response
#' ## matrix
#' probability_matrix <- cbind(
#'     response_probabilities,
#'     1 - response_probabilities
#' )
#' 
<% if (.TYPE == "auc") { %>
#' ## Calculate <%= tolower(.TITLE) %>
#' 
#' SLmetrics::<%= .FUN %>(
#'     actual   = actual_classes, 
#'     response = probability_matrix
#' )
<% } else { %>
#' ## Visualize <%= tolower(.TITLE) %>
#' 
#' plot(
#'     SLmetrics::<%= .FUN %>(
#'      actual   = actual_classes, 
#'      response = probability_matrix
#'  )
#' )
<% } %>
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
