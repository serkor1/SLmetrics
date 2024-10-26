# script: Reciever Operator Characteristics
# date: 2024-10-25
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate Methods
# script start;

#' Compute the \eqn{\text{reciever}} \eqn{\text{operator}} \eqn{\text{characteristics}}
#'
#'
#' @description
#' The [prROC()]-function computes the [precision()] and [recall()] at thresholds provided by the \eqn{response}- or \eqn{thresholds}-vector. The function
#' constructs a [data.frame()] grouped by \eqn{k}-classes where each class is treated as a binary classification problem.
#'
#' @inherit ROC
#'
#' @example man/examples/scr_prROC.R
#'
#' @family classification
#' @family reciever operator characteristics
#'
#' @export
prROC <- function(...) {
  UseMethod(
    generic = "prROC",
    object  = ..1
  )
}

#' @export
print.prROC <- function(x, ...) {

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
plot.prROC <- function(
    x,
    panels = TRUE,
    ...) {

  # 1) Plot options
  #
  # All common options for the
  # plot goes her
  pformula <- precision ~ recall
  groups   <- unique(x$label)
  xlab     <- "Recall"
  ylab     <- "Precision"
  main     <- "Precision-Recall Curve"

  # 1.1) conditional plotting
  # statements
  if (panels) {

    # 1.2) grouped by
    # label.
    pformula <- precision ~ recall | label

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
      columns = length(unique(x$label))
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
