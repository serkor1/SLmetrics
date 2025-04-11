<% 
if (!exists(".SINGLE_OUTPUT", inherits = FALSE)) {
  .SINGLE_OUTPUT <- FALSE
}
value = as.logical(.SINGLE_OUTPUT)
%>
#' @title <%= tools::toTitleCase(.TITLE) %>
#' 
#' @description
#' A S3 generic function for calculating the <%= .FUN %> score of a <%= .TASK %> model. The [<%= .FUN %>()] handles the input as is - and therefore there is not sanity checks. 
#' If the data contains [NA], or `lenght(x) != lenght(y)` you are left at the mercy of compiler.
#' 
#' @returns 
<% if (value) { %>
#' A <[double]>-value 
<% } else { %>
#' @returns If `estimator` is given as
#' \itemize{
#'   \item 0 - a named <[numeric]>-vector of [length] k
#'   \item 1 - a <[double]> value (Micro averaged metric)
#'   \item 2 - a <[double]> value (Macro averaged metric)
#' }
<% } %>
