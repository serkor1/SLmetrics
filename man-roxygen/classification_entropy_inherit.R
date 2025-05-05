#' @inherit <%= .FUN %>
#' 
#' @rdname classification_<%= .FUN %>.<%= .METHOD %>
#' @name <%= .FUN %>.<%= .METHOD %>
#' @method <%= .FUN %> <%= .METHOD %>
#'
#' @examples 
#' ## generate valid probability
#' ## distributions
#' rand.sum <- function(n) {
#'    x <- sort(runif( n-1 ))
#'    c(x,1) - c(0, x)
#' }
<% if ( grepl(pattern = "integer", x = .METHOD) ) { %>
#' ## observed values
#' ## and seed
#' set.seed(1903)
#' actual <- sample(1L:20L, size = 100, replace = TRUE)
#' 
#' ## generate response
#' ## probabilities
#' response <- t(replicate(100, rand.sum(1)))
#' 
#' ## entropy
#' <%= .FUN %>(actual, response)
#' 
<% } %>
#' 
<% if ( grepl(pattern = "factor", x = .METHOD) ) { %>
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
#' response <- t(replicate(1e2, rand.sum(length(classes))))
#' 
#' ## entropy
#' <%= .FUN %>(actual, response)
#' 
<% } %>
#'
<% if ( grepl(pattern = "matrix", x = .METHOD ) ) { %>
#'
#' ## empirical and
#' ## predicted probabilites
#' set.seed(1903)
#' pk <- t(replicate(200,rand.sum(5)))
#' qk <- t(replicate(200,rand.sum(5)))
#' 
#' ## entropy
#' <%= .FUN %>(
#'  pk = pk,
#'  qk = qk
#' )
#' 
<% } %>
#' 
#' @inheritParams classification_documentation
#' @inheritParams entropy_documentation
#' 
#' @keywords entropy
#' @keywords classification
#' @keywords evaluation
#' @concept Machine learning performance evaluation
#' 
#' @references
#' 
#' MacKay, David JC. Information theory, inference and learning algorithms. Cambridge university press, 2003.
#' 
#' Kramer, Oliver, and Oliver Kramer. "Scikit-learn." Machine learning for evolution strategies (2016): 45-53.
#' 
#' Virtanen, Pauli, et al. "SciPy 1.0: fundamental algorithms for scientific computing in Python." Nature methods 17.3 (2020): 261-272.
