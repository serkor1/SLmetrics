#' @inherit <%= .FUN %>
#' 
#' @rdname classification_<%= .FUN %>.<%= .METHOD %>
#' @name <%= .FUN %>.<%= .METHOD %>
#' @method <%= .FUN %> <%= .METHOD %>
#'
#'
<% if ( grepl(pattern = "entropy", x = .METHOD ) ) { %>
#'
#' @examples 
#' ## generate valid probability
#' ## distributions
#' rand.sum <- function(n) {
#'    x <- sort(runif( n-1 ))
#'    c(x,1) - c(0, x)
#' }
#'
#' ## empirical and
#' ## predicted probabilities
#' set.seed(1903)
#' pk <- t(replicate(200,rand.sum(5)))
#' qk <- t(replicate(200,rand.sum(5)))
#' 
#' ## entropy
#' SLmetrics::<%= .FUN %>(
#'  pk = pk,
#'  qk = qk
#' )
#' 
<% } %>
#'
#' 
<% if ( grepl(pattern = "logloss", x = .FUN ) ) { %>
#'
<% if ( grepl(pattern = "weighted", x = .FUN ) ) { %>
#'
#' @examples
#' ## Classes and
#' ## seed
#' set.seed(1903)
#' classes <- c("Kebab", "Falafel")
#' 
#' ## Generate actual
#' ## and predicted response
#' ## probabilities
#' actual_classes <- factor(
#'     x = sample(x = classes, size = 1e3, replace = TRUE),
#'     levels = c("Kebab", "Falafel")
#' )
#' 
#' response <- runif(n = 1e3)
#' 
#' ## Generate sample
#' ## weights
#' sample_weights <- runif(
#'   n = 1e3
#' )
#' 
#' 
#' ## Evaluate performance
#' SLmetrics::<%= .FUN %>(
#'    actual    = actual_classes, 
#'    response  = cbind(
#'      response,
#'      1 - response
#'    ),
#'    w = sample_weights
#' )
#' 
#' ## Generate observed
#' ## frequencies 
#' actual_frequency <- sample(10L:100L, size = 1e3, replace = TRUE)
#' 
#' SLmetrics::<%= .FUN %>(
#'    actual    = actual_frequency, 
#'    response  = response,
#'    w         = sample_weights
#' )
#'
<% } else { %>
#'
#' @examples
#' ## Classes and
#' ## seed
#' set.seed(1903)
#' classes <- c("Kebab", "Falafel")
#' 
#' ## Generate actual
#' ## and predicted response
#' ## probabilities
#' actual_classes <- factor(
#'     x = sample(x = classes, size = 1e3, replace = TRUE),
#'     levels = c("Kebab", "Falafel")
#' )
#' 
#' response <- runif(n = 1e3)
#' 
#' ## Evaluate performance
#' SLmetrics::<%= .FUN %>(
#'    actual    = actual_classes, 
#'    response  = cbind(
#'      response,
#'      1 - response
#'    )
#' )
#' 
#' ## Generate observed
#' ## frequencies 
#' actual_frequency <- sample(10L:100L, size = 1e3, replace = TRUE)
#' 
#' SLmetrics::<%= .FUN %>(
#'    actual    = actual_frequency, 
#'    response  = response
#' )
#' 
#' 
<% } %>
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
