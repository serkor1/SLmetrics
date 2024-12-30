# script: Classification utilities
# for streamlining the unit-tests
# script start;

# Confusion Matrix
confusion_matrix <- function(actual, predicted, w = NULL) {
  if (is.null(w)) {
    SLmetrics::cmatrix(
      actual,
      predicted
    )
  } else {
    SLmetrics::weighted.cmatrix(
      actual,
      predicted,
      w
    )
  }
}

# Classification function:
generalized_metric <- function(
  actual, 
  predicted,
  w = NULL, 
  micro = NULL,
  metric_expr, 
  na.rm = TRUE) {
  
  # 1) Construct confusion matrix
  conf_mat <- confusion_matrix(actual, predicted, w = w)

  # 2) Calculate confusion matrix elements
  TP <- diag(conf_mat)
  FP <- colSums(conf_mat) - TP
  TN <- sum(conf_mat) - rowSums(conf_mat) - colSums(conf_mat) + TP
  FN <- rowSums(conf_mat) - TP

  # 3) Evaluate the metric expression
  output <- eval(substitute(metric_expr))

  if (is.null(micro)) {
    return(output)
  }

  # 4) Aggregate if micro is specified
  if (micro) {
    # Aggregate all values for micro average
    total_TP <- sum(TP, na.rm = TRUE)
    total_FP <- sum(FP, na.rm = TRUE)
    total_TN <- sum(TN, na.rm = TRUE)
    total_FN <- sum(FN, na.rm = TRUE)

    output <- eval(substitute(metric_expr),
                   list(TP = total_TP, FP = total_FP, TN = total_TN, FN = total_FN))
  } else {
    # Handle NA values if na.rm is FALSE
    if (!na.rm) {
      output[!is.finite(output)] <- 0
    }
    # Mean across classes
    output <- mean(output, na.rm = na.rm)
  }

  return(output)
}

# script end;