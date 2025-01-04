#' Compute the Entropy
#'
#' @description
#' The [entropy()] function calculates the **Entropy** of given probability distributions. 
#' 
#' @param pk A \eqn{n \times k} <[numeric]>-matrix of observed probabilities.
#'   The \eqn{i}-th row should sum to 1 (i.e., a valid probability distribution
#'   over the \eqn{k} classes). The first column corresponds to the first factor
#'   level in \code{actual}, the second column to the second factor level, and so on.
#' @param qk A \eqn{n \times k} <[numeric]>-matrix of predicted probabilities.
#'   The \eqn{i}-th row should sum to 1 (i.e., a valid probability distribution
#'   over the \eqn{k} classes). The first column corresponds to the first factor
#'   level in \code{actual}, the second column to the second factor level, and so on.
#' @param dim An <[integer]> value of [length] 1 (Default: 0). Defines the dimensions of to calculate the entropy. 0: Total entropy, 1: row-wise, 2: column-wise
#' @param base A <[numeric]> value of [length] 1 (Default: -1). The logarithmic base to use. Default value specifies natural logarithms.
#' @param ... Arguments passed into other methods
#'
#' @section Calculation:
#' 
#' **Entropy:**
#' \deqn{H(pk) = -\sum_{i} pk_i \log(pk_i)}{H(pk) = -∑ pk_i log(pk_i)}
#' 
#' **Cross Entropy:**
#' \deqn{H(pk, qk) = -\sum_{i} pk_i \log(qk_i)}{H(pk, qk) = -∑ pk_i log(qk_i)}
#' 
#' **Relative Entropy**
#' \deqn{D_{KL}(pk \parallel qk) = \sum_{i} pk_i \log\left(\frac{pk_i}{qk_i}\right)}{D_KL(pk || qk) = ∑ pk_i log(pk_i / qk_i)}
#' 
#' @returns A <[numeric]> value or vector:
#' - A single <[numeric]> value (length 1) if `dim == 0`.
#' - A <[numeric]> vector with length equal to the [length] of rows if `dim == 1`.
#' - A <[numeric]> vector with length equal to the [length] of columns if `dim == 2`.
#' 
#' 
#' @example man/examples/scr_Entropy.R
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

#' @rdname entropy
#' @export
relative.entropy <- function(...) {
  UseMethod(
    generic = "relative.entropy",
    object  = ..1
  )
}

#' @rdname entropy
#' @export
cross.entropy <- function(...) {
  UseMethod(
    generic = "cross.entropy",
    object  = ..1
  )
}