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
#' A genereric function for the [negative likelihood ratio](https://en.wikipedia.org/wiki/Likelihood_ratios_in_diagnostic_testing) in classification tasks. Use [weighted.nlr()] weighted [negative likelihood ratio](https://en.wikipedia.org/wiki/Likelihood_ratios_in_diagnostic_testing).
#' 
#' @section Definition:
#' Let \eqn{\hat{\alpha} \in [0, \infty]} be the likelihood of a negative outcome. The [negative likelihood ratio](https://en.wikipedia.org/wiki/Likelihood_ratios_in_diagnostic_testing) of the classifier is calculated as,
#'
#' \deqn{
#'   \hat{\alpha} = \frac{1 - \frac{\#TP}{\#TP + \#FN}}{\frac{\#TN}{\#TN + \#FP}}
#' }
#'
#' Where:
#' 
#' - \eqn{\frac{\#TP}{\#TP + \#FN}} is the sensitivity, or true positive rate
#' - \eqn{\frac{\#TN}{\#TN + \#FP}} is the specificity, or true negative rate
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
#' A genereric function for the [positive likelihood ratio](https://en.wikipedia.org/wiki/Likelihood_ratios_in_diagnostic_testing) in classification tasks. Use [weighted.plr()] weighted [positive likelihood ratio](https://en.wikipedia.org/wiki/Likelihood_ratios_in_diagnostic_testing).
#' 
#' @section Definition:
#' Let \eqn{\hat{\alpha} \in [0, \infty]} be the likelihood of a positive outcome. The [positive likelihood ratio](https://en.wikipedia.org/wiki/Likelihood_ratios_in_diagnostic_testing) of the classifier is calculated as,
#'
#' \deqn{
#'   \hat{\alpha} = \frac{\frac{\#TP}{\#TP + \#FN}}{1 - \frac{\#TN}{\#TN + \#FP}}
#' }
#'
#' Where:
#' 
#' - \eqn{\frac{\#TP}{\#TP + \#FN}} is the sensitivity, or true positive rate
#' - \eqn{\frac{\#TN}{\#TN + \#FP}} is the specificity, or true negative rate
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
#' A genereric function for the [diagnostic odds ratio](https://en.wikipedia.org/wiki/Diagnostic_odds_ratio) in classification tasks. Use [weighted.dor()] weighted [diagnostic odds ratio](https://en.wikipedia.org/wiki/Diagnostic_odds_ratio).
#' 
#' @section Definition:
#' Let \eqn{\hat{\alpha} \in [0, \infty]} be the effectiveness of the classifier.  The [diagnostic odds ratio](https://en.wikipedia.org/wiki/Diagnostic_odds_ratio) of the classifier is calculated as,
#'
#' \deqn{
#'   \hat{\alpha} = \frac{\text{\#TP} \text{\#TN}}{\text{\#FP} \text{\#FN}}
#' }
#'
#' Where:
#' 
#' - \eqn{\text{\#TP}} is the number of true positives
#' - \eqn{\text{\#TN}} is the number of true negatives
#' - \eqn{\text{\#FP}} is the number of false positives
#' - \eqn{\text{\#FN}} is the number of false negatives
#' 
#' @returns
#' A <[numeric]>-vector of [length] 1
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
