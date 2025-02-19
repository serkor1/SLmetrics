# script: Create a plot of
# the confusion_matrix
# author: Serkan Korkmaz, serkor1@duck.com
# date: 2024-09-20
# objective:
# script start;

#' @inheritSection specificity Creating <[factor]>
#' 
#' @title Confusion Matrix
#'
#' @description
#' The [cmatrix()]-function uses cross-classifying factors to build
#' a confusion matrix of the counts at each combination of the [factor] levels.
#' Each row of the [matrix] represents the actual [factor] levels, while each
#' column represents the predicted [factor] levels.
#'
#' @usage
#' ## Generic S3 method
#' cmatrix(
#'  actual,
#'  predicted,
#'  ...
#' )
#' 
#' @param actual A <[factor]>-vector of [length] \eqn{n}, and \eqn{k} levels.
#' @param predicted A <[factor]>-vector of [length] \eqn{n}, and \eqn{k} levels.
#' @param w A <[numeric]>-vector of [length] \eqn{n} (default: [NULL]) If passed it will return a weighted confusion matrix.
#' @param ... Arguments passed into other methods.
#' 
#' @section Dimensions:
#' There is no robust defensive measure against mis-specifying
#' the confusion matrix. If the arguments are correctly specified, the resulting
#' confusion matrix is on the form:
#'
#' |            | A (Predicted) | B (Predicted) |
#' | :----------|:-------------:| -------------:|
#' | A (Actual) | Value         | Value         |
#' | B (Actual) | Value         | Value         |
#'
#'
#' @returns
#' A named \eqn{k} x \eqn{k} <[matrix]>
#'
#' @example man/examples/scr_ConfusionMatrix.R
#' 
#' @family Classification
#' @family Supervised Learning
#' 
#' @export
cmatrix <- function(
  actual,
  predicted,
  ...) {
  UseMethod(
    generic = "cmatrix"
  )
}

#' @rdname cmatrix
#' @usage
#' ## Generic S3 method
#' weighted.cmatrix(
#'  actual,
#'  predicted,
#'  w,
#'  ...
#' )
#' @export
weighted.cmatrix <- function(
  actual,
  predicted,
  w,
  ...) {
  UseMethod(
    generic = "weighted.cmatrix"
  )
}

#' @export
print.cmatrix <- function(
    x,
    ...) {

  print.table(
    x,
    ...
    )

}

#' @export
plot.cmatrix <- function(
    x,
    main = NULL,
    ...) {

  # 1) check input
  # from user
  main <- if (is.null(main)) NULL else main


  lattice::levelplot(
    x[, ncol(x):1],  # Reverse the column order
    pretty = TRUE,
    xlab = "Actual",
    ylab = "Predicted",
    main = main,
    margin = FALSE,
    colorkey = FALSE,
    panel = function(...) {

      lattice::panel.levelplot(...)  # Draw the levelplot

      # Add labels (numbers) to the heatmap cells
      for (i in 1:nrow(x)) {
        for (j in 1:ncol(x)) {
          # Adjust the text labels to correspond to the flipped matrix
          lattice::panel.text(i, j, labels = t(x)[i, ncol(x) - j + 1], col = "black")
        }
      }

    },
    scales = list(
      x = list(alternating = 2)
    )
  )

}

#' @export
summary.cmatrix <- function(
    object,
    average = "micro",
    digits = 2,
    ...) {

  micro <- average == "micro"

  # 1) print the header
  # of the summary
  cat(
    "Confusion Matrix",
    paste0("(", paste(dim(object),collapse = " x "), ")"),
    "\n"
  )

  full_line()

  print(object)

  full_line()

  # summary statistics
  #
  cat(
    paste("Overall Statistics", paste0("(", paste(average, "average"), ")")),
    paste(" - Accuracy:         ", formatC(accuracy(object), digits = digits,format = "f")),
    paste(" - Balanced Accuracy:", formatC(baccuracy(object), digits = digits,format = "f")),
    paste(" - Sensitivity:      ", formatC(sensitivity(object,micro = micro), digits = digits, format = "f")),
    paste(" - Specificity:      ", formatC(specificity(object,micro = micro), digits = digits, format = "f")),
    paste(" - Precision:        ", formatC(precision(object,micro = micro), digits = digits, format = "f")),
    sep = "\n"
    )

}

# script end;
