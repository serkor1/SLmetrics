#' Compute the \eqn{\text{Cross}} \eqn{\text{Entropy}} \eqn{\text{Loss}}
#'
#' @description
#' The [entropy()] function computes the **Cross-Entropy Loss** — often called  **Log Loss** — between observed classes (as a <[factor]>) and their predicted probability distributions (a <[numeric]> matrix). 
#' The [weighted.entropy()] function is the weighted version, applying observation-specific weights.
#'
#' @inherit accuracy
#' @param response A \eqn{N \times k} <[numeric]>-matrix of predicted probabilities.
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
#' If \code{normalize = TRUE}, this sum is divided by \eqn{N} (the number of observations). When weights \eqn{w_i} are supplied, each term is multiplied by \eqn{w_i}, and if \code{normalize = TRUE}, the final sum is divided by \eqn{\sum_i w_i}.
#' 
#' @example man/examples/scr_CrossEntropyLoss.R
#'
#' @family Classification
#' @family Supervised Learning
#'
#' @aliases entropy logloss
#'
#' @export
entropy <- function(...) {
  UseMethod(
    generic = "entropy",
    object  = ..1
  )
}

#' @rdname entropy
#' @export
weighted.entropy <- function(...) {
  UseMethod(
    generic = "weighted.entropy",
    object  = ..1
  )
}

#' @rdname entropy
#' @export
logloss <- function(...) {
  UseMethod(
    generic = "logloss",
    object  = ..1
  )
}

#' @rdname entropy
#' @export
weighted.logloss <- function(...) {
  UseMethod(
    generic = "weighted.logloss",
    object  = ..1
  )
}