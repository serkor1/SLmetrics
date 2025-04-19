#' @inherit <%= .FUN %>
#' 
#' @rdname regression_<%= .FUN %>.<%= .METHOD %>
#' @name <%= .FUN %>.<%= .METHOD %>
#' @method <%= .FUN %> <%= .METHOD %>
#' @inheritParams regression_documentation
#' 
#' @examples
<% if (grepl(pattern = "weighted", x = .FUN)) { %>
#' ## Generate actual
#' ## and predicted values
#' actual_values    <- c(1.3, 0.4, 1.2, 1.4, 1.9, 1.0, 1.2)
#' predicted_values <- c(0.7, 0.5, 1.1, 1.2, 1.8, 1.1, 0.2)
#' 
#' ## Generate sample
#' ## weights
#' sample_weights <- c(0.3, 0.5, 0.3, 0, 0.8, 0.8, 1)
#' 
#' ## Evaluate performance
#' SLmetrics::<%= .FUN %>(
#'    actual    = actual_values, 
#'    predicted = predicted_values,
#'    w         = sample_weights
#' )
<% } else { %>
#' ## Generate actual
#' ## and predicted values
#' actual_values    <- c(1.3, 0.4, 1.2, 1.4, 1.9, 1.0, 1.2)
#' predicted_values <- c(0.7, 0.5, 1.1, 1.2, 1.8, 1.1, 0.2)
#' 
#' ## Evaluate performance
#' SLmetrics::<%= .FUN %>(
#'    actual    = actual_values, 
#'    predicted = predicted_values
#' )
<% } %>
#'
#' @keywords regression
#' @keywords evaluation
#' @concept Machine learning performance evaluation
#' 
#' @references
#' 
#' James, Gareth, et al. An introduction to statistical learning. Vol. 112. No. 1. New York: springer, 2013.
#' 
#' Hastie, Trevor. "The elements of statistical learning: data mining, inference, and prediction." (2009).
#' 
#' Virtanen, Pauli, et al. "SciPy 1.0: fundamental algorithms for scientific computing in Python." Nature methods 17.3 (2020): 261-272.
#' 
#' Pedregosa, Fabian, et al. "Scikit-learn: Machine learning in Python." the Journal of machine Learning research 12 (2011): 2825-2830.
