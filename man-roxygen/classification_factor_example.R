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
#' ## Evaluate performance
#' SLmetrics::<%= .FUN %>(
#'    actual_classes, 
#'    predicted_classes
#' )
