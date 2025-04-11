# script: Accuracy
# date: 2024-10-05
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate methods for accuracy
# script start;

#' @templateVar .TITLE accuracy
#' @templateVar .FUN accuracy
#' @templateVar .TASK Classification
#' @templateVar .SINGLE_OUTPUT TRUE
#' @template classification_inheritDotParams
#' @template classification_factor_example
#' @template classification_cmatrix_template
#'
#' @usage
#' ## Generic S3 method
#' ## for unweighted accuracy
#' accuracy(...)
#'
#' @family Classification
#' @family Supervised Learning
#' 
#' @export
accuracy <- function(...) {
  UseMethod(
    generic = "accuracy",
    object  = ..1
  )
}

#' @rdname accuracy
#' @usage
#' ## Generic S3 method
#' ## for weighted accuracy
#' weighted.accuracy(...)
#' @export
weighted.accuracy <- function(...) {
  UseMethod(
    generic = "weighted.accuracy",
    object  = ..1
  )
}

# script end;
