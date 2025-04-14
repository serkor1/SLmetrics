#' @title <%= tools::toTitleCase(.TITLE) %>
#' @rdname <%= .FUN %>
#' @name <%= .FUN %>
#' 
#' @description
#' A S3 generic function for calculating the <%= tolower(.TITLE) %> score of a <%= tolower(.TASK) %> model. [<%= .FUN %>()] handles the input as is - and therefore there is not sanity checks. 
#' If the data contains [NA], or `length(x) != length(y)` you are left at the mercy of compiler.
#' 
#' ## Defensive measures
#' 
#' As everything is based on pointers internally values as [NA] and out of bounds values (`length(x) != length(y)`) the compiler does not know how to react - this is undefined behaviour. And therefore it is not enough to wrap your call in `try()` or `tryCatch()` to recover from sudden errors. Your `R`-session *will* most likely just crash.
#' A workaroud is to create a wrapper around [<%= .FUN %>()] and any other evaluation metrics you are planning to use, and do the sanity checks before it reaches [<%= .FUN %>()].
#'
#' @usage 
#' ## Generic S3 method
#' ## for <%= tools::toTitleCase(.TITLE) %>
#' <%= .FUN %>(...)
#' 
#' 
#' @keywords entropy
#' @keywords classification
#' @keywords evaluation
#' @concept Machine learning performance evaluation
#' 
#' @family Classification
#' @family Supervised Learning
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
#' Virtanen, Pauli, et al. "SciPy 1.0: fundamental algorithms for scientific computing in Python." Nature methods 17.3 (2020): 261-272.
