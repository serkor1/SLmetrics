# script: specificity
# author: Serkan Korkmaz, serkor1@duck.com
# date: 2024-10-02
# objective: Generate method
# script start;

#' Specificity or \eqn{\text{true}} \eqn{\text{negative}} \eqn{\text{rate}}
#'
#' @description
#' The  [specificity()]-function computes the [specificity](https://en.wikipedia.org/wiki/Sensitivity_and_specificity), also known as the True Negative Rate (TNR) or selectivity, between
#' two vectors of predicted and observed [factor()] values. The [weighted.specificity()] function computes the weighted specificity.
#'
#' @param actual A vector of <[factor]>- of [length] \eqn{n}, and \eqn{k} levels.
#' @param predicted A vector of <[factor]>-vector of [length] \eqn{n}, and \eqn{k} levels.
#' @param w A <[numeric]>-vector of [length] \eqn{n}. [NULL] by default. 
#' @param x A confusion matrix created [cmatrix()].
#' @param micro A <[logical]>-value of [length] \eqn{1} (default: [NULL]). If [TRUE] it returns the
#' micro average across all \eqn{k} classes, if [FALSE] it returns the macro average.
#' @param na.rm A <[logical]> value of [length] \eqn{1} (default: [TRUE]). If [TRUE], [NA] values are removed from the computation. 
#' This argument is only relevant when `micro != NULL`. 
#' When `na.rm = TRUE`, the computation corresponds to `sum(c(1, 2, NA), na.rm = TRUE) / length(na.omit(c(1, 2, NA)))`.
#' When `na.rm = FALSE`, the computation corresponds to `sum(c(1, 2, NA), na.rm = TRUE) / length(c(1, 2, NA))`.
#' @param ... Arguments passed into other methods
#' 
#' @section Creating <[factor]>:
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
#' If `micro` is [NULL] (the default), a named <[numeric]>-vector of [length] k
#'
#' If `micro` is [TRUE] or [FALSE], a <[numeric]>-vector of [length] 1
#'
#' @example man/examples/scr_Specificity.R
#'
#'
#' @section Calculation:
#' 
#' The metric is calculated for each class \eqn{k} as follows,
#'
#' \deqn{
#'   \frac{\#TN_k}{\#TN_k+\#FP_k}
#' }
#'
#' Where \eqn{\#TN_k} and \eqn{\#FP_k} is the number of true negatives and false positives, respectively, for each class \eqn{k}.
#' 
#' @family Classification
#' @family Supervised Learning
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

#' @rdname specificity
#' @export
weighted.specificity <- function(...) {
  UseMethod(
    generic = "weighted.specificity",
    object  = ..1
  )
}

#' @rdname specificity
#' @export
weighted.tnr <- function(...) {
  UseMethod(
    generic = "weighted.tnr",
    object  = ..1
  )
}

#' @rdname specificity
#' @export
weighted.selectivity <- function(...) {
  UseMethod(
    generic = "weighted.selectivity",
    object  = ..1
  )
}

# script end;
