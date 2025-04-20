<% if (grepl(pattern = "logloss", x = .FUN)) { %>
#'
#' @inheritDotParams <%= .FUN %>.integer
#' @inheritDotParams <%= .FUN %>.factor
#' 
<% } else { %>
#'
#' @inheritDotParams <%= .FUN %>.matrix
#' 
<% } %>
#'
#' 
<% if (grepl(pattern = "logloss", x = .FUN)) { %>
#' @returns 
#' A <[double]>
<% } else { %>
#' @returns A <[double]> value or vector:
#' - A single <[double]> value (length 1) if `dim == 0`.
#' - A <[double]> vector with length equal to the [length] of rows if `dim == 1`.
#' - A <[double]> vector with length equal to the [length] of columns if `dim == 2`.
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
