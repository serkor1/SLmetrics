# script: Reciever Operator Characteristics
# date: 2024-10-25
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate Methods
# script start;

#' @inherit ROC
#'
#' @title Precision-Recall Curve
#'
#' @description
#' The [prROC()]-function computes the [precision()] and [recall()] at thresholds provided by the \eqn{response}- or \eqn{thresholds}-vector. The function
#' constructs a [data.frame()] grouped by \eqn{k}-classes where each class is treated as a binary classification problem.
#' 
#' @returns A [data.frame] on the following form,
#'
#' \item{threshold}{<[numeric]> Thresholds used to determine [recall()] and [precision()]}
#' \item{level}{<[character]> The level of the actual <[factor]>}
#' \item{label}{<[character]> The levels of the actual <[factor]>}
#' \item{recall}{<[numeric]> The recall}
#' \item{precision}{<[numeric]> The precision}
#'
#' @example man/examples/scr_PrecisionRecallCurve.R
#'
#' @family Classification
#' @family Supervised Learning
#' 
#' @export
prROC <- function(...) {
  UseMethod(
    generic = "prROC",
    object  = ..1
  )
}

#' @rdname prROC
#' @export
weighted.prROC <- function(...) {
  UseMethod(
    generic = "weighted.prROC",
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
summary.prROC <- function(
  object,
  ...) {
  
  # 1) calculate area 
  # under the curve

  # 1.1) extract list
  # of labels
  x_list <- split(
    x = object,
    f = object$label
  )

  # 1.2) calculate AUC
  # for each label
  metric <- vapply(
    x_list, 
    function(x) {
      auc(
        y = x$precision,
        x = x$recall
      )
    }, 
    FUN.VALUE = numeric(1),
    USE.NAMES = TRUE
  )

  names(metric) <- names(x_list)
  
  structure(
    .Data = {
      list(
        auc = metric
      )
    },
    class = "summary.prROC"
  )
  
}

#' @export
print.summary.prROC <- function(
  x,
  ...) {

  cat("Reciever Operator Characteristics", "\n")
  full_line()
  cat(
    "AUC",
    paste0(" - ",names(x$auc), ": ", round(x$auc, 3)),
    sep = "\n"
  )

  invisible(x)

}

#' @export
plot.prROC <- function(
    x,
    panels = TRUE,
    ...) {
  
    # 0) exract the finite
    # data.frame
    x <- x[is.finite(x$threshold), ]

    # 1) Plot options
    #
    # All common options for the
    # plot goes her
    pformula <- precision ~ recall
    groups   <- x$label
    xlab     <- "Recall"
    ylab     <- "Precision"
    main     <- "Precision-Recall Curve"

    # 1.1) conditional plotting
    # statements
    if (panels) {

      # 1.2) grouped by
      # label.
      pformula <- precision ~ recall | factor(label, labels = unique(label))

      # 1.3) disable grouping
      # if panelwise
      groups  <- NULL

    }

    roc_plot(
      formula  = pformula,
      groups   = groups,
      xlab     = xlab,
      ylab     = ylab,
      main     = main,
      DT       = x,
      add_poly = panels,
      ...  
    )

}

# script end;
