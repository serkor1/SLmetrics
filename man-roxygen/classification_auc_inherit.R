#' @inherit <%= .FUN %>
#'
#' @rdname classification_<%= .FUN %>.<%= .METHOD %>
#' @name <%= .FUN %>.<%= .METHOD %>
#' @method <%= .FUN %> <%= .METHOD %>
#' 
#' @inheritParams classification_documentation
#' 
#' @examples
#' ## Classes and
#' ## seed
#' set.seed(1903)
#' classes <- c("Kebab", "Falafel")
#' 
#' ## Generate actual classes
#' ## and response probabilities
#' actual <- factor(
#'     x = sample(
#'       x = classes, 
#'       size = 1e2, 
#'       replace = TRUE, 
#'       prob = c(0.7, 0.3)
#'     )
#' )
#' 
#' response <- ifelse(
#'     actual == "Kebab", 
#'     rbeta(sum(actual == "Kebab"), 2, 5), 
#'     rbeta(sum(actual == "Falafel"), 5, 2)
#' )
#' 
<% if (grepl(pattern = "weighted", x = .FUN)) { %>
#'
#' w <- runif(1e2)
#'
<% if (.TYPE == "auc") { %>
#' ## Evaluate performance
#' 
#' SLmetrics::<%= .FUN %>(
#'     actual   = actual, 
#'     response = response,
#'     w = w
#' )
#' 
<% } else { %>
#'
#' ## Visualize
#' 
#' plot(
#'     SLmetrics::<%= .FUN %>(
#'      actual   = actual, 
#'      response = response.
#'      w = w
#'  )
#' )
#' 
#' 
<% } %>
#'
<% } else { %>
#' 
<% if (.TYPE == "auc") { %>
#' ## Evaluate performance
#' 
#' SLmetrics::<%= .FUN %>(
#'     actual   = actual, 
#'     response = response
#' )
#' 
<% } else { %>
#'
#' ## Visualize
#' 
#' plot(
#'     SLmetrics::<%= .FUN %>(
#'      actual   = actual, 
#'      response = response
#'  )
#' )
#' 
<% } %>
<% } %>
#' 
#' @keywords classification
#' @keywords evaluation
#' @concept Machine learning performance evaluation
#' 
#' @references
#' 
#' James, Gareth, et al. An introduction to statistical learning. Vol. 112. No. 1. New York: springer, 2013.
#' 
#' Hastie, Trevor. "The elements of statistical learning: data mining, inference, and prediction." (2009).
#' 
#' Pedregosa, Fabian, et al. "Scikit-learn: Machine learning in Python." the Journal of machine Learning research 12 (2011): 2825-2830.
