# script: specificity
# author: Serkan Korkmaz, serkor1@duck.com
# date: 2024-10-02
# objective: Generate method
# script start;

#' @aliases specificity tnr selectivity
#' @title Specificity
#'
#' @description
#' A generic funcion for the [Specificity](https://en.wikipedia.org/wiki/Sensitivity_and_specificity). Use [weighted.specificity()] for the weighted [Specificity](https://en.wikipedia.org/wiki/Sensitivity_and_specificity).
#' 
#' ## Other names
#' True Negative Rate, Selectivity
#' 
#' @usage 
#' ## Generic S3 method
#' specificity(
#'  ...,
#'  micro = NULL,
#'  na.rm = TRUE
#' )
#'
#' @param actual A vector of <[factor]> values of [length] \eqn{n}, and \eqn{k} levels.
#' @param predicted A vector of <[factor]> values of [length] \eqn{n}, and \eqn{k} levels.
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
#' @section Definition:
#' Let \eqn{\hat{\sigma} \in [0, 1]} be the proportion of true negatives among the actual negatives. The specificity of the classifier is calculated as,
#'
#' \deqn{
#'   \hat{\sigma} = \frac{\#TN_k}{\#TN_k + \#FP_k}
#' }
#'
#' Where:
#' 
#' - \eqn{\#TN_k} is the number of true negatives, and
#' - \eqn{\#FP_k} is the number of false positives.
#'
#' @example man/examples/scr_Specificity.R
#'
#' @family Classification
#' @family Supervised Learning
#' 
#' @export
specificity <- function(
  ..., 
  micro = NULL, 
  na.rm = TRUE) {
  UseMethod(
    generic = "specificity",
    object  = ..1
  )
}

#' @rdname specificity
#' @usage 
#' ## Generic S3 method
#' tnr(
#'  ...,
#'  micro = NULL,
#'  na.rm = TRUE
#' )
#' @export
tnr <- function(
  ..., 
  micro = NULL, 
  na.rm = TRUE) {
  UseMethod(
    generic = "tnr",
    object  = ..1
  )
}

#' @rdname specificity
#' @usage 
#' ## Generic S3 method
#' selectivity(
#'  ...,
#'  micro = NULL,
#'  na.rm = TRUE
#' )
#' @export
selectivity <- function(
  ..., 
  micro = NULL, 
  na.rm = TRUE) {
  UseMethod(
    generic = "selectivity",
    object  = ..1
  )
}

#' @rdname specificity
#' @usage 
#' ## Generic S3 method
#' weighted.specificity(
#'  ...,
#'  w,
#'  micro = NULL,
#'  na.rm = TRUE
#' )
#' @export
weighted.specificity <- function(
  ...,
  w,
  micro = NULL, 
  na.rm = TRUE) {
  UseMethod(
    generic = "weighted.specificity",
    object  = ..1
  )
}

#' @rdname specificity
#' @usage 
#' ## Generic S3 method
#' weighted.tnr(
#'  ...,
#'  w,
#'  micro = NULL,
#'  na.rm = TRUE
#' )
#' @export
weighted.tnr <- function(
  ...,
  w,
  micro = NULL, 
  na.rm = TRUE) {
  UseMethod(
    generic = "weighted.tnr",
    object  = ..1
  )
}

#' @rdname specificity
#' @usage 
#' ## Generic S3 method
#' weighted.selectivity(
#'  ...,
#'  w,
#'  micro = NULL,
#'  na.rm = TRUE
#' )
#' @export
weighted.selectivity <- function(
  ...,
  w,
  micro = NULL, 
  na.rm = TRUE) {
  UseMethod(
    generic = "weighted.selectivity",
    object  = ..1
  )
}

# script end;
