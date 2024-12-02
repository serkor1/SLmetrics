# script: Likelihood Methods
# date: 2024-10-05
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate Likelihood
# methods. Combines Positive, Negative and Diagnostic Odds Ratio
# script start;

#' Compute the \eqn{\text{negative}} \eqn{\text{likelihood}} \eqn{\text{ratio}}
#'
#' @description
#' The [nlr()]-function computes the [negative likelihood ratio](https://en.wikipedia.org/wiki/Likelihood_ratios_in_diagnostic_testing), also known as the likelihood ratio for negative results, between
#' two vectors of predicted and observed [factor()] values.
#'
#' When `aggregate = TRUE`, the function returns the micro-average NLR across all classes \eqn{k}.
#' By default, it returns the class-wise NLR.
#'
#' @example man/examples/scr_nlr.R
#'
#' @inherit specificity
#'
#' @section Calculation:
#'
#' The metric is calculated for each class \eqn{k} as follows,
#'
#' \deqn{
#'   \frac{1 - \text{Sensitivity}_k}{\text{Specificity}_k}
#' }
#'
#' Where sensitivity (or true positive rate) is calculated as \eqn{\frac{\#TP_k}{\#TP_k + \#FN_k}} and specificity (or true negative rate) is calculated as \eqn{\frac{\#TN_k}{\#TN_k + \#FP_k}}.
#'
#' When `aggregate = TRUE`, the `micro`-average is calculated,
#'
#' \deqn{
#'   \frac{\sum_{k=1}^k (1 - \text{Sensitivity}_k)}{\sum_{k=1}^k \text{Specificity}_k}
#' }
#'
#' @seealso
#'
#' The [plr()]-function for the Positive Likehood Ratio (LR+)
#'
#' @family classification
#'
#' @export
nlr <- function(...) {
  UseMethod(
    generic = "nlr",
    object  = ..1
  )
}

#' Compute the \eqn{\text{positive}} \eqn{\text{likelihood}} \eqn{\text{ratio}}
#'
#' @description
#' The [plr()]-function computes the [positive likelihood ratio](https://en.wikipedia.org/wiki/Likelihood_ratios_in_diagnostic_testing), also known as the likelihood ratio for positive results, between
#' two vectors of predicted and observed [factor()] values.
#'
#' When `aggregate = TRUE`, the function returns the micro-average PLR across all classes \eqn{k}.
#' By default, it returns the class-wise PLR.
#'
#' @example man/examples/scr_plr.R
#'
#' @inherit specificity
#'
#' @section Calculation:
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
#' @family classification
#' @export
plr <- function(...) {
  UseMethod(
    generic = "plr",
    object  = ..1
  )
}

#' Compute the \eqn{\text{diagnostic}} \eqn{\text{odds}} \eqn{\text{ratio}}
#'
#' @description
#' The [dor()]-function computes the [Diagnostic Odds Ratio](https://en.wikipedia.org/wiki/Diagnostic_odds_ratio) (DOR), a single indicator of test performance, between
#' two vectors of predicted and observed [factor()] values.
#'
#' When `aggregate = TRUE`, the function returns the micro-average DOR across all classes \eqn{k}. By default, it returns the class-wise DOR.
#'
#' @example man/examples/scr_diagnosticodssratio.R
#'
#' @inherit specificity
#'
#' @section Calculation:
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
#' @family classification
#'
#' @export
dor <- function(...) {
  UseMethod(
    generic = "dor",
    object  = ..1
  )
}

# script end;
