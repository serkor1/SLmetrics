# script: Area Under the  Curve
# author: Serkan Korkmaz, serkor1@duck.com
# date: 2025-22-02
# objective: Generate method
# script start;

#' @title AUC
#' 
#' @description
#' The [auc()]-function calculates the area under the curve.
#' 
#' @usage
#' ## Generic S3 method
#' auc(
#'  y,
#'  x,
#'  method = 0,
#'  presorted = TRUE,
#'  ...
#' )
#' 
#' @param y A <[numeric]> vector of [length] \eqn{n}.
#' @param x A <[numeric]> vector of [length] \eqn{n}.
#' @param method A <[numeric]> value (default: \eqn{0}). Defines the underlying method of calculating the area under the curve. If \eqn{0} it is calculated using the `trapezoid`-method, if \eqn{1} it is calculated using the `step`-method.
#' @param presorted A <[logical]>-value [length] 1 (default: [FALSE]). If [TRUE] the input will not be sorted by threshold.
#' @param ... Arguments passed into other methods.
#' 
#' @returns 
#' A <[numeric]>  vector  of [length] 1
#' 
#' @example man/examples/scr_AreaUnderTheCurve.R
#' 
#' @family Tools
#' 
#' @export
auc <- function(
  y,
  x,
  method  = 0,
  presorted = TRUE,
  ...) {
  UseMethod(
    generic = "auc"
  )
}

#' @inherit specificity
#' @inherit ROC
#' @inherit auc
#' 
#' @usage
#' ## Generic S3 method
#' pr.auc(
#'  actual,
#'  response,
#'  micro  = NULL,
#'  method = 0,
#'  ...
#' )
#' 
#' @example man/examples/scr_PrecisionRecallAUC.R
#' 
#' @export
pr.auc <- function(
  actual,
  response,
  micro = NULL,
  method  = 0,
  ...) {
  UseMethod(
    generic = "pr.auc",
    object  = response 
  )
}

#' @rdname pr.auc
#' @inherit ROC
#' @inherit auc
#' @inherit specificity
#' 
#' @description
#' A generic function for the area under the Precision-Recall Curve in classification tasks. Use [weighted.pr.auc()] for the weighted area under the Precision-Recall Curve.
#' 
#' 
#' @usage
#' ## Generic S3 method
#' weighted.pr.auc(
#'  actual,
#'  response,
#'  w,
#'  micro  = NULL,
#'  method = 0,
#'  ...
#' )
#' 
#' @export
weighted.pr.auc <- function(
  actual,
  response,
  w,
  micro = NULL,
  method  = 0,
  ...) {
  UseMethod(
    generic = "weighted.pr.auc",
    object  = response 
  )
}

#' @inherit specificity
#' @inherit ROC
#' @inherit auc
#' 
#' @description
#' A generic function for the area under the Receiver Operator Characteristics Curve in classification tasks. Use [weighted.roc.auc()] for the weighted area under the Receiver Operator Characteristics Curve.
#' 
#' @usage
#' ## Generic S3 method
#' roc.auc(
#'  actual,
#'  response,
#'  micro  = NULL,
#'  method = 0,
#'  ...
#' )
#'
#' @example man/examples/scr_ReceiverOperatorCurveAUC.R
#' 
#' 
#' @export
roc.auc <- function(
  actual,
  response,
  micro = NULL,
  method  = 0,
  ...) {
  UseMethod(
    generic = "roc.auc",
    object  = response 
  )
}

#' @rdname roc.auc
#' @inherit ROC
#' @inherit auc
#' @inherit specificity
#' @usage
#' ## Generic S3 method
#' weighted.roc.auc(
#'  actual,
#'  response,
#'  w,
#'  micro  = NULL,
#'  method = 0,
#'  ...
#' )
#' @export
weighted.roc.auc <- function(
  actual,
  response,
  w,
  micro = NULL,
  method  = 0,
  ...) {
  UseMethod(
    generic = "weighted.roc.auc",
    object  = response 
  )
}

# script end;
