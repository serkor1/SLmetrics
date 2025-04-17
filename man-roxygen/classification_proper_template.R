#' @title <%= tools::toTitleCase(.TITLE) %>
#' @rdname <%= .FUN %>
#' @name <%= .FUN %>
#' 
#' @keywords classification
#' @keywords evaluation
#' @concept Machine learning performance evaluation
#' 
#' @description
#' A S3 generic function for calculating the <%= tolower(.TITLE) %> of a <%= tolower(.TASK) %> model. [<%= .FUN %>()] handles the input as is - and therefore there are no sanity checks. 
#' If the data contains [NA], or `length(x) != length(y)` you are left at the mercy of compiler.
#'
#' ## Defensive measures
#' 
#' As everything is based on pointers internally values as [NA] and out of bounds values (`length(x) != length(y)`) the compiler does not know how to react - this is undefined behaviour. And therefore it is not enough to wrap your call in `try()` or `tryCatch()` to recover from sudden errors. Your `R`-session *will* most likely just crash.
#' A workaround is to create a wrapper around [<%= .FUN %>()] and any other evaluation metrics you are planning to use, and do the sanity checks before it reaches [<%= .FUN %>()].
#'
#' @usage
#' ## Generic S3 method
#' ## for <%= tools::toTitleCase(.TITLE) %>
#' <%= .FUN %>(...)
#' 
#' @inheritDotParams <%= .FUN %>.matrix
#' @inheritDotParams weighted.<%= .FUN %>.matrix
#' 
#' @returns 
#' A <[double]>-value 
#' 
#' @family Classification
#' @family Proper scoring rules
#' @family Supervised Learning
#' 
#' @examples
#' ## seed
#' set.seed(1903)
#' 
#' ## The general setup
#' ## with 3 classes
#' n_obs     <- 10
#' n_classes <- 3
#' 
#' ## Generate indicator matrix
#' ## with observed outcome (ok) and 
#' ## its predicted probability matrix (qk)
#' ok <- diag(n_classes)[ sample.int(n_classes, n_obs, TRUE), ]
#' qk <- matrix(runif(n_obs * n_classes), n_obs, n_classes)
#' qk <- qk / rowSums(qk)
#' 
#' ## Evaluate performance
#' SLmetrics::<%= .FUN %>(
#'    ok = ok, 
#'    qk = qk
#' )
#' 
#' @references
#' 
#' Gneiting, Tilmann, and Adrian E. Raftery. "Strictly proper scoring rules, prediction, and estimation." Journal of the American statistical Association 102.477 (2007): 359-378.
#' 
#' James, Gareth, et al. An introduction to statistical learning. Vol. 112. No. 1. New York: springer, 2013.
#' 
#' Hastie, Trevor. "The elements of statistical learning: data mining, inference, and prediction." (2009).
#' 
#' Pedregosa, Fabian, et al. "Scikit-learn: Machine learning in Python." the Journal of machine Learning research 12 (2011): 2825-2830.
