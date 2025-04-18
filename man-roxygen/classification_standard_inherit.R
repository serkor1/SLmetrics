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
<% if (tolower(.METHOD) == "factor" && !grepl(pattern = "weighted", x = .FUN)) { %>
#' ## Evaluate performance
#' SLmetrics::<%= .FUN %>(
#'    actual_classes, 
#'    predicted_classes
#' )
<% } %>
#' 
<% if (tolower(.METHOD) == "cmatrix") { %>
#' ## Construct confusion
#' ## matrix
#' confusion_matrix <- SLmetrics::cmatrix(
#'     actual    = actual_classes,
#'     predicted = predicted_classes
#' )
#' 
#' ## Evaluate performance
#' SLmetrics::<%= .FUN %>(confusion_matrix)
<% } %>
#' 
<% if (tolower(.METHOD) == "factor" && grepl(pattern = "weighted", x = .FUN)) { %>
#' ## Generate sample
#' ## weights
#' sample_weights <- runif(
#'    n = length(actual_classes)
#' )
#' 
#' ## Evaluate performance
#' SLmetrics::<%= .FUN %>(
#'    actual_classes, 
#'    predicted_classes, 
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
