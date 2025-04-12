#' @title <%= tools::toTitleCase(.TITLE) %>
#' @rdname <%= .FUN %>
#' @name <%= .FUN %>
#' 
#' @description
#' A S3 generic function for calculating the <%= tolower(.TITLE) %> score of a <%= tolower(.TASK) %> model. [<%= .FUN %>()] handles the input as is - and therefore there is not sanity checks. 
#' If the data contains [NA], or `length(x) != length(y)` you are left at the mercy of compiler.
#' 
<% if (.TYPE != "auc") { %>
#' ## Area under the curve
#' 
#' Use [auc.<%= .FUN %>] for calculating the area under the curve directly.
#' 
<% } else { %>
#' ## Constructing data.frames
#' 
#' Description for the main function
#' 
#' Use [<%= .FUN %>] for calculating the area under the curve directly.
#' 
<% } %>
#' 
#' ## Defensive measures
#' 
#' As everything is based on pointers internally values as [NA] and out of bounds values (`length(x) != length(y)`) the compiler does not know how to react - this is undefined behaviour. And therefore it is not enough to wrap your call in `try()` or `tryCatch()` to recover from sudden errors. Your `R`-session *will* most likely just crash.
#' A workaroud is to create a wrapper around [<%= .FUN %>()] and any other evaluation metrics you are planning to use, and do the sanity checks before it reaches [<%= .FUN %>()].