#' 
<% if (grepl(pattern = "logloss", x = .FUN)) { %>
#'
#' @inheritDotParams <%= .FUN %>.integer
#' @inheritDotParams <%= .FUN %>.factor
#' 
#' @inheritDotParams weighted.<%= .FUN %>.integer
#' @inheritDotParams weighted.<%= .FUN %>.factor
#' 
#' 
#' @examples
#' ## Classes and
#' ## seed
#' set.seed(1903)
#' classes <- c("Kebab", "Falafel")
#' 
#' ## Generate actual
#' ## and predicted response
#' ## probabilites
#' actual_classes <- factor(
#'     x = sample(x = classes, size = 1e3, replace = TRUE),
#'     levels = c("Kebab", "Falafel")
#' )
#' 
#' response <- runif(n = 1e3)
#' 
#' ## Logloss
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
#' ## Poisson Logloss
#' SLmetrics::<%= .FUN %>(
#'    actual    = actual_frequency, 
#'    response  = response
#' )
#' 
#' 
#' 
<% } else { %>
#'
#' @inheritDotParams <%= .FUN %>.matrix
#' 
#' @examples 
#' ## generate valid probability
#' ## distributions
#' rand.sum <- function(n) {
#'    x <- sort(runif( n-1 ))
#'    c(x,1) - c(0, x)
#' }
#' 
<% if (!grepl(pattern = "shannon", x = .FUN)) { %>
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
<% } else { %>
#' 
#' 
#' ## empirical and
#' ## predicted probabilites
#' set.seed(1903)
#' pk <- t(replicate(200,rand.sum(5)))
#' 
#' ## entropy
#' SLmetrics::<%= .FUN %>(
#'  pk = pk
#' )
#' 
#' 
<% } %>
<% } %>
#' 
#' 
<% if (grepl(pattern = "logloss", x = .FUN)) { %>
#' @returns 
#' A <[double]>
<% } else { %>
#' @returns A <[double]> value or vector:
#' - A single <[double]> value (length 1) if `dim == 0`.
#' - A <[double]> vector with length equal to the [length] of columns if `dim == 1`.
#' - A <[double]> vector with length equal to the [length] of rows if `dim == 2`.
<% } %>
#' 
#' @references
#' 
#' MacKay, David JC. Information theory, inference and learning algorithms. Cambridge university press, 2003.
#' 
#' Kramer, Oliver, and Oliver Kramer. "Scikit-learn." Machine learning for evolution strategies (2016): 45-53.
#' 
#' Virtanen, Pauli, et al. "SciPy 1.0: f'undamental algorithms for scientific computing in Python." Nature methods 17.3 (2020): 261-272.
#' 
#' @family Classification
#' @family Supervised Learning
#' @family Entropy
#' @keywords entropy
