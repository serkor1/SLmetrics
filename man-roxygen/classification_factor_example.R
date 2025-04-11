#' @examples
#' ## Generate actual
#' ## and predicted classes
#' actual_classes    <- factor(c(1,2,1,2,2,3,4))
#' predicted_classes <- factor(c(1,2,1,2,2,3,4))
#' 
#' ## Evaluate performance
#' SLmetrics::<%= .FUN %>(
#'    actual_classes, 
#'    predicted_classes
#' )
