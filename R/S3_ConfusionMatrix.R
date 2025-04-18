# script: Create a plot of
# the confusion_matrix
# author: Serkan Korkmaz, serkor1@duck.com
# date: 2024-09-20
# objective:
# script start;

#' @title NULL
#' @usage NULL
#' @returns NULL
#' 
#' @templateVar .TITLE Confusion Matrix
#' @templateVar .FUN cmatrix
#' @templateVar .TASK classification
#' 
#' @template generic_description
#' 
#' @description
#' 
#' ## The workhorse
#' 
#' [cmatrix()] is the main function for classification metrics with cmatrix S3 dispatch. These functions internally calls [cmatrix()], so there is a signficant gain in computing the confusion matrix first, and then pass it onto the metrics.
#' For example:
#' 
#' ```r
#' ## Compute confusion matrix
#' confusion_matrix <- cmatrix(actual, predicted)
#' 
#' ## Evaluate accuracy
#' ## via S3 dispatching
#' accuracy(confusion_matrix)
#' 
#' ## Evaluate recall
#' ## via S3 dispatching
#' recall(confusion_matrix)
#' ```
#' 
#' 
#' @inheritDotParams cmatrix.factor
#' @inheritDotParams weighted.cmatrix.factor
#' 
#' @section Dimensions:
#' There is no robust defensive measure against misspecifying the confusion matrix. If the arguments are passed correctly, the resulting
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
#' 
#' @examples
#' ## Classes and
#' ## seed
#' set.seed(1903)
#' classes <- c("Kebab", "Falafel")
#' 
#' ## Generate actual
#' ## and predicted classes
#' actual_classes <- factor(
#'     x = sample(x = classes, size = 1e3, replace = TRUE),
#'     levels = c("Kebab", "Falafel")
#' )
#' 
#' predicted_classes <- factor(
#'     x = sample(x = classes, size = 1e3, replace = TRUE),
#'     levels = c("Kebab", "Falafel")
#' )
#' 
#' ## Compute the confusion
#' ## matrix
#' SLmetrics::cmatrix(
#'  actual    = actual_classes, 
#'  predicted = predicted_classes
#' )
#' 
#' @references
#' 
#' James, Gareth, et al. An introduction to statistical learning. Vol. 112. No. 1. New York: springer, 2013.
#' 
#' Hastie, Trevor. "The elements of statistical learning: data mining, inference, and prediction." (2009).
#' 
#' Pedregosa, Fabian, et al. "Scikit-learn: Machine learning in Python." the Journal of machine Learning research 12 (2011): 2825-2830.
#' 
#' @family Classification
#' @family Supervised Learning
#' 
#' @export
cmatrix <- function(...) {
  UseMethod(
    generic = "cmatrix"
  )
}

#' @usage NULL
#' 
#' @templateVar .TITLE confusion matrix
#' @templateVar .FUN cmatrix
#' @templateVar .TASK Classification
#' 
#' @template generic_inherit
#' 
#' @export
weighted.cmatrix <- function(...) {
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
    estimator = "micro",
    digits = 2,
    ...) {
  
  # 0) determine aggregation
  # level based on estimator
  # 
  # Can be passed as <character>
  # <numeric> or <integer>
  estimator <- switch (estimator,
    "micro" = {1},
    "macro" = {2},
    # default value:
    1
  )

  # pass the chosen
  # value to average
  average <- switch (estimator,
    "micro",
    "macro"
  ) 
  
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
  # for the classification
  # problem
  cat(
    paste("Overall Statistics", paste0("(", paste(average, "average"), ")")),
    paste(" - Accuracy:         ", formatC(accuracy(object), digits = digits,format = "f")),
    paste(" - Balanced Accuracy:", formatC(baccuracy(object), digits = digits,format = "f")),
    paste(" - Sensitivity:      ", formatC(sensitivity(object,estimator = estimator), digits = digits, format = "f")),
    paste(" - Specificity:      ", formatC(specificity(object,estimator = estimator), digits = digits, format = "f")),
    paste(" - Precision:        ", formatC(precision(object,estimator = estimator), digits = digits, format = "f")),
    sep = "\n"
    )
}

# script end;
