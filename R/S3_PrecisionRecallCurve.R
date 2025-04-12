# script: Precision Recall Curve
# date: 2024-10-25
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate Methods
# script start;

#' @templateVar .TITLE Precision Recall Curve
#' @templateVar .FUN pr.curve
#' @templateVar .TYPE not_auc
#' @templateVar .TASK Classification
#' @template classification_auc_params
#' @template classification_auc_template
#' 
#' @usage
#' ## Generic S3 method
#' ## for unweighted Precision
#' ## Recall Curve
#' pr.curve(...)
#' 
#' @returns A [data.frame] on the following form,
#'
#' \item{threshold}{<[numeric]> Thresholds used to determine [recall()] and [precision()]}
#' \item{level}{<[character]> The level of the actual <[factor]>}
#' \item{label}{<[character]> The levels of the actual <[factor]>}
#' \item{recall}{<[numeric]> The recall}
#' \item{precision}{<[numeric]> The precision}
#'
#' @family Classification
#' @family Supervised Learning
#' 
#' @export
pr.curve <- function(...) {
  UseMethod(
    generic = "pr.curve"
  )
}

#' @rdname pr.curve
#' @usage
#' ## Generic S3 method
#' ## for weighted Precision
#' ## Recall Curve
#' weighted.pr.curve(...)
#' @export
weighted.pr.curve <- function(...) {
  UseMethod(
    generic = "weighted.pr.curve"
  )
}

#' @templateVar .TITLE Area under the Precision Recall Curve
#' @templateVar .FUN auc.pr.curve
#' @templateVar .TYPE auc
#' @templateVar .TASK Classification
#' @template classification_auc_params
#' @template classification_auc_template
#' 
#' @usage
#' ## Generic S3 method for
#' ## unweighted area under the
#' ## Precision Recall Curve
#' auc.pr.curve(...)
#' 
#' @rawNamespace export(auc.pr.curve)
auc.pr.curve <- function(...) {
  UseMethod(
    generic = "auc.pr.curve"
  )
}

#' @rdname auc.pr.curve
#' @usage
#' ## Generic S3 method for
#' ## weighted area under the
#' ## Precision Recall Curve
#' weighted.auc.pr.curve(...)
#' 
#' @rawNamespace export(weighted.auc.pr.curve)
weighted.auc.pr.curve <- function(...) {
  UseMethod(
    generic = "weighted.auc.pr.curve"
  )
}

#' @export
print.pr.curve <- function(x, ...) {

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
summary.pr.curve <- function(
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
    class = "summary.prc"
  )
  
}

#' @export
print.summary.pr.curve <- function(
  x,
  ...) {

  cat("Precision Recall Curve", "\n")
  full_line()
  cat(
    "AUC",
    paste0(" - ",names(x$auc), ": ", round(x$auc, 3)),
    sep = "\n"
  )

  invisible(x)

}

#' @export
plot.pr.curve <- function(
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
