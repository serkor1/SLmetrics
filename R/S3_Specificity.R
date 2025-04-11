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
#' True Negative Rate ([tnr()])
#' Selectivity ([selectivity()])
#' 
#' @usage 
#' ## Generic S3 method
#' ## for unweighted specificity
#' specificity(...)
#' 
#' @inheritDotParams specificity.factor
#' @inheritDotParams weighted.specificity.factor
#' @inheritDotParams specificity.cmatrix
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
#' @returns If `estimator` is giveen as
#' \itemize{
#'   \item 0 - a named <[numeric]>-vector of [length] k (class-wise)
#'   \item 1 - a <[numeric]> value (Micro averaged metric)
#'   \item 2 - a <[numeric]> value (macro averaged metric)
#' }
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
#' @templateVar fun specificity
#' @template factor_template
#'
#' @family Classification
#' @family Supervised Learning
#' 
#' @export
specificity <- function(...) {
  UseMethod(
    generic = "specificity",
    object  = ..1
  )
}

#' @rdname specificity
#' @usage 
#' ## Generic S3 method
#' ## for weighted specificity
#' weighted.specificity(...)
#' @export
weighted.specificity <- function(...) {
    UseMethod(
      generic = "weighted.specificity",
      object  = ..1
    )
  }


#' @export
tnr <- function(...) {
  UseMethod(
    generic = "tnr",
    object  = ..1
  )
}

#' @export
weighted.tnr <- function(...) {
    UseMethod(
      generic = "weighted.tnr",
      object  = ..1
    )
  }

#' @export
selectivity <- function(...) {
  UseMethod(
    generic = "selectivity",
    object  = ..1
  )
}

#' @export
weighted.selectivity <- function(...) {
  UseMethod(
    generic = "weighted.selectivity",
    object  = ..1
  )
}

# script end;
