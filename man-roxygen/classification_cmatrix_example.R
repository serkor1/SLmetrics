#' @examples
#' ## Generate actual
#' ## and predicted classes
#' actual_classes    <- factor(c(1,2,1,2,2,3,4))
#' predicted_classes <- factor(c(1,2,1,2,2,3,4))
#' 
#' ## Construct confusion
#' ## matrix
#' confusion_matrix <- SLmetrics::cmatrix(
#'     actual    = actual_classes,
#'     predicted = predicted_classes
#' )
#' 
#' ## Evaluate performance
#' SLmetrics::<%= .FUN %>(confusion_matrix)
