#' @inherit <%= .FUN %>
#' 
#' @rdname <%= .FUN %>.<%= .METHOD %>
#' @name <%= .FUN %>.<%= .METHOD %>
#' @method <%= .FUN %> <%= .METHOD %>
#' @inheritParams classification_documentation
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
<% if (tolower(.METHOD) == "numeric" && !grepl(pattern = "weighted", x = .FUN)) { %>
#' ## Evaluate performance
#' SLmetrics::<%= .FUN %>(
#'    p = p, 
#'    q = q
#' )
<% } %>
#' 
<% if (tolower(.METHOD) == "numeric" && grepl(pattern = "weighted", x = .FUN)) { %>
#' ## Generate sample
#' ## weights
#' sample_weights <- runif(
#'    n = length(p)
#' )
#' 
#' ## Evaluate performance
#' SLmetrics::<%= .FUN %>(
#'    p = p, 
#'    q = q, 
#'    sample_weights
#' )
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
