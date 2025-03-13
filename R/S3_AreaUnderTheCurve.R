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
#' @section Definition:
#' 
#' **Trapezoidal rule**
#' 
#' The **trapezoidal rule** approximates the integral of a function \eqn{f(x)} between
#' \eqn{x = a} and \eqn{x = b} using trapezoids formed between consecutive points. If
#' we have points \eqn{x_0, x_1, \ldots, x_n} (with \eqn{a = x_0 < x_1 < \cdots < x_n = b})
#' and corresponding function values \eqn{f(x_0), f(x_1), \ldots, f(x_n)}, the area under
#' the curve \eqn{A_T} is approximated by:
#' 
#' \deqn{
#'   A_T \approx \sum_{k=1}^{n} \frac{f(x_{k-1}) + f(x_k)}{2} \bigl[x_k - x_{k-1}\bigr].
#' }
#' 
#' **Step-function method**
#'
#' The **step-function (rectangular) method** uses the value of the function at one
#' endpoint of each subinterval to form rectangles. With the same partition
#' \eqn{x_0, x_1, \ldots, x_n}, the rectangular approximation \eqn{A_S} can be written as:
#' 
#' \deqn{
#'   A_S \approx \sum_{k=1}^{n} f(x_{k-1}) \bigl[x_k - x_{k-1}\bigr].
#' }
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

#' @inherit auc
#' @inheritParams ROC
#' @inheritParams specificity
#' @inherit specificity return
#' 
#' @title Area under the Precision-Recall Curve
#' 
#' @description
#' A generic function for the area under the Precision-Recall Curve. Use [weighted.pr.auc()] for the weighted area under the Precision-Recall Curve.
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
#' @family Classification
#' @family Supervised Learning
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
#' @inherit auc
#' @inheritParams ROC
#' @inherit specificity return
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
#' @family Classification
#' @family Supervised Learning
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

#' @inherit auc
#' @inheritParams ROC
#' @inheritParams specificity
#' @inherit specificity return
#' 
#' @title Area under the Receiver Operator Characteristics Curve
#' 
#' @description
#' A generic function for the area under the Receiver Operator Characteristics Curve. Use [weighted.roc.auc()] for the weighted area under the Receiver Operator Characteristics Curve.
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
#' @family Classification
#' @family Supervised Learning
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
#' @inherit auc
#' @inheritParams ROC
#' @inheritParams specificity
#' @inherit specificity return
#' 
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
#' 
#' @family Classification
#' @family Supervised Learning
#' 
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
