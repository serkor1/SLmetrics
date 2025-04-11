#' @examples
#' ## Generate actual
#' ## and predicted classes
#' actual_classes <- factor(
#'     x = c("kebab", "kebab", "kebab", "kebab", "Falafel", "Falafel", "Falafel", "Falafel"),
#'     levels = c("kebab", "Falafel")
#' )
#' 
#' predicted_classes <- factor(
#'     x = c("kebab", "kebab", "Falafel", "Falafel", "Falafel", "Falafel", "kebab", "kebab"),
#'     levels = c("kebab", "Falafel")
#')
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
