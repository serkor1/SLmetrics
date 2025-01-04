#' Compute the Log Loss
#'
#' @description
#' The [logloss()] function computes the **Log Loss** between observed classes (as a <[factor]>) and their predicted probability distributions (a <[numeric]> matrix). The [weighted.logloss()] function is the weighted version, applying observation-specific weights.
#'
#' @inherit accuracy
#' @param response A \eqn{n \times k} <[numeric]>-matrix of predicted probabilities.
#'   The \eqn{i}-th row should sum to 1 (i.e., a valid probability distribution
#'   over the \eqn{k} classes). The first column corresponds to the first factor
#'   level in \code{actual}, the second column to the second factor level, and so on.
#' @param normalize A <[logical]>-value (default: [TRUE]). If [TRUE],
#'   the mean cross-entropy across all observations is returned; otherwise, the
#'   sum of cross-entropies is returned.
#'
#' @section Calculation:
#'
#' Let \eqn{y_{i,k}} be the one-hot encoding of the actual class label for the \eqn{i}-th observation (that is, \eqn{y_{i,k} = 1} if observation \eqn{i} belongs to class \eqn{k}, and 0 otherwise), and let \eqn{\hat{p}_{i,k}} be the predicted probability of class \eqn{k} for observation \eqn{i}. 
#' The cross-entropy loss \eqn{L} is:
#'
#' \deqn{
#'   L = -\sum_{i=1}^N \sum_{k=1}^K y_{i,k}\,\log(\hat{p}_{i,k}).
#' }
#'
#' This can be interpreted as the **Cross-Entropy** between the true distribution \( P \) and the predicted distribution \( Q \), where:
#'
#' \deqn{
#'   H(P, Q) = H(P) + D_{KL}(P \parallel Q)
#' }
#'
#' Here, \( H(P) \) is the **Entropy** of the true distribution, and \( D_{KL}(P \parallel Q) \) is the **Kullback-Leibler Divergence** (Relative Entropy) from \( P \) to \( Q \). If \code{normalize = TRUE}, this sum is divided by \eqn{N} (the number of observations). When weights \eqn{w_i} are supplied, each term is multiplied by \eqn{w_i}, and if \code{normalize = TRUE}, the final sum is divided by \eqn{\sum_i w_i}.
#' 
#' @example man/examples/scr_LogLoss.R
#'
#' @family Classification
#' @family Supervised Learning
#'
#' @aliases logloss
#'
#' @export
logloss <- function(...) {
  UseMethod(
    generic = "logloss",
    object  = ..1
  )
}

#' @rdname logloss
#' @export
weighted.logloss <- function(...) {
  UseMethod(
    generic = "weighted.logloss",
    object  = ..1
  )
}