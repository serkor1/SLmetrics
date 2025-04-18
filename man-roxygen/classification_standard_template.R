#' @inheritDotParams <%= .FUN %>.factor
#' @inheritDotParams weighted.<%= .FUN %>.factor
#' @inheritDotParams <%= .FUN %>.cmatrix
#' 
<% if ( tolower(.MULTI_OUTPUT) == 'false' ) { %>
#' @returns 
#' A <[double]>-value
<% } else { %>
#' @returns If `estimator` is given as
#' \itemize{
#'   \item 0 - a named <[double]> vector of [length] k
#'   \item 1 - a <[double]> value (Micro averaged metric)
#'   \item 2 - a <[double]> value (Macro averaged metric)
#' }
<% } %>
#'
#' @examples
#' ## Classes and
#' ## seed
#' set.seed(1903)
#' classes <- c("Kebab", "Falafel")
#' 
#' ## Generate actual
#' ## and predicted classes
#' actual_classes <- factor(
#'     x = sample(x = classes, size = 10, replace = TRUE),
#'     levels = c("Kebab", "Falafel")
#' )
#' 
#' predicted_classes <- factor(
#'     x = sample(x = classes, size = 10, replace = TRUE),
#'     levels = c("Kebab", "Falafel")
#')
#' 
#' ## Evaluate performance
#' SLmetrics::<%= .FUN %>(
#'    actual_classes, 
#'    predicted_classes
#' )
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
