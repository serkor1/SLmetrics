# script: Precision Recall Curve
# date: 2024-10-25
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate Methods
# script start;

#' @title NULL
#' @usage NULL
#' 
#' @templateVar .TITLE Precision Recall Curve
#' @templateVar .FUN pr.curve
#' @templateVar .TYPE not_auc
#' @templateVar .TASK Classification
#' 
#' @template generic_description
#' @template classification_auc_template
#' 
#' @returns A [data.frame] on the following form,
#'
#' \item{threshold}{<[numeric]> Thresholds used to determine [recall()] and [precision()]}
#' \item{level}{<[character]> The level of the actual <[factor]>}
#' \item{label}{<[character]> The levels of the actual <[factor]>}
#' \item{recall}{<[numeric]> The recall}
#' \item{precision}{<[numeric]> The precision}
#' 
#' @export
pr.curve <- function(...) {
  UseMethod(
    generic = "pr.curve"
  )
}

#' @usage NULL
#' 
#' @templateVar .TITLE Precision Recall Curve
#' @templateVar .FUN pr.curve
#' @templateVar .TASK Classification
#' 
#' @template generic_inherit
#' 
#' @export
weighted.pr.curve <- function(...) {
  UseMethod(
    generic = "weighted.pr.curve"
  )
}

#' @title NULL
#' @usage NULL
#' @returns NULL
#' 
#' @templateVar .TITLE Area under the Precision Recall Curve
#' @templateVar .FUN auc.pr.curve
#' @templateVar .TYPE auc
#' @templateVar .TASK Classification
#' 
#' @template generic_description
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

#' @usage NULL
#' 
#' @templateVar .TITLE Area under the Precision Recall Curve
#' @templateVar .FUN auc.pr.curve
#' @templateVar .TASK Classification
#' 
#' @template generic_inherit
#' 
#' @rawNamespace export(weighted.auc.pr.curve)
weighted.auc.pr.curve <- function(...) {
  UseMethod(
    generic = "weighted.auc.pr.curve"
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
      auc.xy(
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
print.summary.prROC <- function(
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
