# script: Reciever Operator Characteristics
# date: 2024-10-25
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate Methods
# script start;

#' Compute the \eqn{\text{reciever}} \eqn{\text{operator}} \eqn{\text{characteristics}}
#'
#'
#' @description
#' The [ROC()]-function computes the [tpr()] and [fpr()] at thresholds provided by the \eqn{response}- or \eqn{thresholds}-vector. The function
#' constructs a [data.frame()] grouped by \eqn{k}-classes where each class is treated as a binary classification problem.
#'
#'
#' @inherit specificity
#' @param response A <[numeric]>-vector of [length] \eqn{n}. The estimated response probabilities.
#' @param thresholds An optional <[numeric]>-vector of non-zero [length]. [NULL] by default.
#' @param ... Arguments passed into other methods.
#'
#'
#' @example man/examples/scr_ROC.R
#'
#' @returns A [data.frame] on the following form,
#'
#' \item{thresholds}{<[numeric]> Thresholds used to determine [tpr()] and [fpr()]}
#' \item{level}{<[character]> The level of the actual <[factor]>}
#' \item{label}{<[character]> The levels of the actual <[factor]>}
#' \item{fpr}{<[numeric]> The false positive rate}
#' \item{tpr}{<[numeric]> The true positve rate}
#'
#' @family classification
#' @family reciever operator characteristics
#'
#' @export
ROC <- function(...) {
  UseMethod(
    generic = "ROC",
    object  = ..1
  )
}

#' @export
print.ROC <- function(x, ...) {

  print.data.frame(
    x,
    ...,
    digits = 3,
    max = sum(
      rep(
        10,
        ncol(x)
      )
    )
  )

}


#' @export
plot.ROC <- function(
    x,
    panels = TRUE,
    ...) {



  # 1) Plot options
  #
  # All common options for the
  # plot goes her
  pformula <- tpr ~ fpr
  groups   <- unique(x$label)
  xlab     <- "False Positive Rate (FPR)"
  ylab     <- "True Positive Rate (TPR)"
  main     <- "Reciever Operator Characteristics"

  # 1.1) conditional plotting
  # statements
  if (panels) {

    # 1.2) grouped by
    # label.
    pformula <- tpr ~ fpr | label

    # 1.3) disable grouping
    # if panelwise
    groups  <- NULL

  }

  lattice::xyplot(
    x        = pformula,
    data     = x,
    groups   = groups,
    type     = "l",
    xlab     = xlab,
    ylab     = ylab,
    main     = main,
    lwd      = 2,
    auto.key = list(
      space = "bottom",
      columns = length(groups)
    ),
    xlim = c(0, 1),
    ylim = c(0, 1),
    panel = function(x, y, ...) {

      lattice::panel.xyplot(x, y, ...)
      lattice::panel.abline(
        a = 0,
        b = 1,
        lty = 2
      )

    },
    ...

  )
}

# script end;
