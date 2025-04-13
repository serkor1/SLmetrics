#' @title <%= tools::toTitleCase(.TITLE) %>
#' 
<% if (.TYPE == "auc") { %>
#'
#' @rdname <%= .FUN %>.<%= .METHOD %>
#' @name <%= .FUN %>.<%= .METHOD %>
#' 
<% } else { %>
#'
#' @rdname <%= .FUN %>.<%= .METHOD %>
#' @name <%= .FUN %>.<%= .METHOD %>
#' 
<% } %>
#'
#' @method <%= .FUN %> <%= .METHOD %>
#' @inheritParams classification_documentation
#' 
#' @keywords classification
#' @keywords evaluation
#' @concept Machine learning performance evaluation
