# script: Create a plot of
# the confusion_matrix
# author: Serkan Korkmaz, serkor1@duck.com
# date: 2024-09-20
# objective:
# script start;

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
