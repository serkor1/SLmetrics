# script: specificity
# author: Serkan Korkmaz, serkor1@duck.com
# date: 2024-10-02
# objective: Generate method
# script start;

#' Specificity (True Negative Rate)
#'
#' @description
#' The  [specificity()]-function computes the [specificity](https://en.wikipedia.org/wiki/Sensitivity_and_specificity), also known as the True Negative Rate (TNR) or selectivity, between
#' two vectors of predicted and observed [factor()] values. When `aggregate = TRUE`, the function returns the micro-average specificity across all classes \eqn{k}.
#' By default, it returns the class-wise specificity.
#'
#' @inheritParams cmatrix
#' @param ... Arguments passed into other methods.
#' @param x A confusion matrix created by [table()] or [cmatrix()]
#' @param micro A <[logical]>-value of [length] \eqn{1}. [NULL] by default. If [TRUE] it returns the
#' micro average across all \eqn{k} classes, if [FALSE] it returns the macro average. Otherwise class wise performance evaluation.
#' @param na.rm A <[logical]>-value of [length] \eqn{1}. [TRUE] by default. If [FALSE] [NA] values will be disregarded when `micro = FALSE`.
#'
#' @details
#'
#' Consider a classification problem with three classes: `A`, `B`, and `C`. The actual vector of [factor()] values is defined as follows:
#'
#' ```{r output, echo = TRUE}
#' ## set seed
#' set.seed(1903)
#'
#' ## actual
#' factor(
#'   x = sample(x = 1:3, size = 10, replace = TRUE),
#'   levels = c(1, 2, 3),
#'   labels = c("A", "B", "C")
#' )
#' ```
#'
#' Here, the values 1, 2, and 3 are mapped to `A`, `B`, and `C`, respectively. Now, suppose your model does not predict any `B`'s. The predicted vector of [factor()] values would be defined as follows:
#'
#' ```{r output, echo = TRUE}
#' ## set seed
#' set.seed(1903)
#'
#' ## predicted
#' factor(
#'   x = sample(x = c(1, 3), size = 10, replace = TRUE),
#'   levels = c(1, 2, 3),
#'   labels = c("A", "B", "C")
#' )
#' ```
#'
#' In both cases, \eqn{k = 3}, determined indirectly by the `levels` argument.
#'
#' @returns
#'
#' If `aggregate` is [FALSE] (the default), a named <[numeric]>-vector of [length] k
#'
#' If `aggregate` is [TRUE], a <[numeric]>-vector of [length] 1
#'
#' @example man/examples/scr_specificity.R
#'
#'
#' @section Calculation:
#' The metric is calculated for each class \eqn{k} as follows,
#'
#' \deqn{
#'   \frac{\#TN_k}{\#TN_k+\#FP_k}
#' }
#'
#' Where \eqn{\#TN_k} and \eqn{\#FP_k} is the number of true negatives and false positives, respectively, for each class \eqn{k}.
#'
#' When `aggregate = TRUE` the `micro`-average is calculated,
#'
#' \deqn{
#'   \frac{\sum_{k=1}^k \#TN_k}{\sum_{k=1}^k \#TN_k + \sum_{k=1}^k \#FP_k}
#' }
#'
#'
#' @family classification
#'
#' @aliases specificity tnr selectivity
#'
#' @export
specificity <- function(...) {
  UseMethod(
    generic = "specificity",
    object  = ..1
  )
}

#' @rdname specificity
#' @export
tnr <- function(...) {
  UseMethod(
    generic = "tnr",
    object  = ..1
  )
}

#' @rdname specificity
#' @export
selectivity <- function(...) {
  UseMethod(
    generic = "selectivity",
    object  = ..1
  )
}

# script end;
