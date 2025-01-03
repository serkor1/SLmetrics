#' Compute the \eqn{\text{Cross}} \eqn{\text{Entropy}} \eqn{\text{Loss}}
#'
#' @description
#' The [entropy()] function computes the **Cross-Entropy Loss** — often called  **Log Loss** — between observed classes (as a <[factor]>) and their predicted probability distributions (a <[numeric]> matrix).
#'
#' @param pk A <[numeric]> matrix.
#' @param axis An <[integer]> value of [length] 1 (Default: 0). Defines the dimensions of to calculate the entropy. 0: Total entropy, 1: row-wise, 2: column-wise
#' @param base A <[numeric]> value of [length] 1 (Default: -1). The logarithmic base to use. Default value specifies natural logarithms.
#' @param ... Arguments passed into other methods
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
#'
#' @family Classification
#' @family Supervised Learning
#'
#' @aliases entropy
#'
#' @export
entropy <- function(...) {
  UseMethod(
    generic = "entropy",
    object  = ..1
  )
}