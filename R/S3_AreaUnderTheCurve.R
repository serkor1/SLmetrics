# script: Area Under the  Curve
# author: Serkan Korkmaz, serkor1@duck.com
# date: 2025-22-02
# objective: Generate method
# script start;

#' @title Area under the curve
#' @rdname tools_auc.xy
#' 
#' @description
#' The [auc.xy()]-function calculates the area under the curve.
#' 
#' @usage
#' ## Generic S3 method
#' auc.xy(...)
#' 
#' @inheritDotParams auc.xy.numeric
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
#' A <[double]> value.
#' 
#' 
#' @family Tools
#' 
#' @export
auc.xy <- function(...) {
  UseMethod(
    generic = "auc.xy"
  )
}

# script end;
