# script: Likelihood Methods
# date: 2024-10-05
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate Likelihood
# methods. Combines Positive, Negative and Diagnostic Odds Ratio
# script start;

#' @inherit specificity
#' 
#' @title Negative Likelihood Ratio
#'
#' @description
#' The [nlr()]-function computes the [negative likelihood ratio](https://en.wikipedia.org/wiki/Likelihood_ratios_in_diagnostic_testing), also known as the likelihood ratio for negative results, between
#' two vectors of predicted and observed [factor()] values. The [weighted.nlr()] function computes the weighted negative likelihood ratio.
#'
#' @section Definition:
#'
#' The metric is calculated for each class \eqn{k} as follows,
#'
#' \deqn{
#'   \frac{1 - \text{Sensitivity}_k}{\text{Specificity}_k}
#' }
#'
#' Where sensitivity (or true positive rate) is calculated as \eqn{\frac{\#TP_k}{\#TP_k + \#FN_k}} and specificity (or true negative rate) is calculated as \eqn{\frac{\#TN_k}{\#TN_k + \#FP_k}}.
#' 
#' @seealso
#'
#' The [plr()]-function for the Positive Likehood Ratio (LR+)
#'
#' @example man/examples/scr_NegativeLikelihoodRatio.R
#' 
#' @family Classification
#' @family Supervised Learning
#'
#' @export
nlr <- function(...) {
  UseMethod(
    generic = "nlr",
    object  = ..1
  )
}

#' @rdname nlr
#' @export
weighted.nlr <- function(...) {
  UseMethod(
    generic = "weighted.nlr",
    object  = ..1
  )
}

#' @inherit specificity
#' 
#' @title Positive Likelihood Ratio
#'
#' @description
#' The [plr()]-function computes the [positive likelihood ratio](https://en.wikipedia.org/wiki/Likelihood_ratios_in_diagnostic_testing), also known as the likelihood ratio for positive results, between
#' two vectors of predicted and observed [factor()] values.  The [weighted.plr()] function computes the weighted positive likelihood ratio.
#'
#' @section Definition:
#'
#' The metric is calculated for each class \eqn{k} as follows,
#'
#' \deqn{
#'   \frac{\text{Sensitivity}_k}{1 - \text{Specificity}_k}
#' }
#'
#' Where sensitivity (or true positive rate) is calculated as \eqn{\frac{\#TP_k}{\#TP_k + \#FN_k}} and specificity (or true negative rate) is calculated as \eqn{\frac{\#TN_k}{\#TN_k + \#FP_k}}.
#'
#' When `aggregate = TRUE`, the `micro`-average is calculated,
#'
#' \deqn{
#'   \frac{\sum_{k=1}^k \text{Sensitivity}_k}{1 - \sum_{k=1}^k \text{Specificity}_k}
#' }
#'
#' @seealso
#'
#' The [nlr()]-function for the Negative Likehood Ratio (LR-)
#'
#' @example man/examples/scr_PositiveLikelihoodRatio.R
#' 
#' @family Classification
#' @family Supervised Learning
#' 
#' @export
plr <- function(...) {
  UseMethod(
    generic = "plr",
    object  = ..1
  )
}

#' @rdname plr
#' @export
weighted.plr <- function(...) {
  UseMethod(
    generic = "weighted.plr",
    object  = ..1
  )
}

#' @inherit specificity
#' 
#' @title Diagnostic Odds Ratio
#'
#' @description
#' The [dor()]-function computes the [Diagnostic Odds Ratio](https://en.wikipedia.org/wiki/Diagnostic_odds_ratio) (DOR), a single indicator of test performance, between
#' two vectors of predicted and observed [factor()] values. The [weighted.dor()] function computes the weighted diagnostic odds ratio.
#'
#' When `aggregate = TRUE`, the function returns the micro-average DOR across all classes \eqn{k}. By default, it returns the class-wise DOR.
#' 
#' @section Definition:
#'
#' The metric is calculated for each class \eqn{k} as follows,
#'
#' \deqn{
#'   \text{DOR}_k = \frac{\text{PLR}_k}{\text{NLR}_k}
#' }
#'
#' Where \eqn{\text{PLR}_k} and \eqn{\text{NLR}_k} is the positive and negative likelihood ratio for class \eqn{k}, respectively. See [plr()] and [nlr()] for more details.
#'
#' When `aggregate = TRUE`, the `micro`-average is calculated as,
#'
#' \deqn{
#'   \overline{\text{DOR}} = \frac{\overline{\text{PLR}_k}}{\overline{\text{NLR}_k}}
#' }
#'
#' Where \eqn{\overline{\text{PLR}}} and \eqn{\overline{\text{NLR}}} is the micro-averaged is the positive and negative likelihood ratio, respectively.
#'
#' @example man/examples/scr_DiagnosticOddsRatio.R
#' 
#' @family Classification
#' @family Supervised Learning
#'
#' @export
dor <- function(...) {
  UseMethod(
    generic = "dor",
    object  = ..1
  )
}

#' @rdname dor
#' @export
weighted.dor <- function(...) {
  UseMethod(
    generic = "weighted.dor",
    object  = ..1
  )
}


# script end;
