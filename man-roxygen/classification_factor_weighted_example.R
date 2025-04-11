#' @examples
#' ## Generate actual
#' ## and predicted classes
#' actual_classes    <- factor(c(1,2,1,2,2,3,4))
#' predicted_classes <- factor(c(1,2,1,2,2,3,4))
#' 
#' ## Generate sample
#' ## weights
#' sample_weights <- runif(
#'    n = length(actual_classes)
#' )
#' 
#' ## Evaluate performance
#' SLmetrics::weighted.<%= .FUN %>(
#'    actual_classes, 
#'    predicted_classes, 
#'    sample_weights
#' )
