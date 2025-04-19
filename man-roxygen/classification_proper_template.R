#' @inheritDotParams <%= .FUN %>.matrix
#' @inheritDotParams weighted.<%= .FUN %>.matrix
#' 
#' @returns 
#' A <[double]>-value 
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
#' 
#' @family Classification
#' @family Proper scoring rules
#' @family Supervised Learning
