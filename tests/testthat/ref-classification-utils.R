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
  estimator = 0,
  metric_expr, 
  na.rm = TRUE,
  ...) {
  
  # 1) Construct confusion matrix
  conf_mat <- confusion_matrix(actual, predicted, w = w)

  # 2) Calculate confusion matrix elements
  TP <- diag(conf_mat)
  FP <- colSums(conf_mat) - TP
  TN <- sum(conf_mat) - rowSums(conf_mat) - colSums(conf_mat) + TP
  FN <- rowSums(conf_mat) - TP

  # 3) Evaluate the metric expression
  
  # 3.1) construct values with ellipsis
  env <- c(list(TP = TP, FP = FP, TN = TN, FN = FN), list(...))

  # 3.2) calculate output
  output <- eval(substitute(metric_expr), envir = env)

  switch (estimator + 1,
     {
      return(output)
    },
    {

      # Aggregate all values for micro average
      total_TP <- sum(TP, na.rm = TRUE)
      total_FP <- sum(FP, na.rm = TRUE)
      total_TN <- sum(TN, na.rm = TRUE)
      total_FN <- sum(FN, na.rm = TRUE)

      env <- c(list(TP = total_TP, FP = total_FP, TN = total_TN, FN = total_FN), list(...))
      output <- eval(substitute(metric_expr), envir = env)
      return(output)

    },
    {
      # Handle NA values if na.rm is FALSE
      if (!na.rm) {
        output[!is.finite(output)] <- 0
      }
      # Mean across classes
      output <- mean(output, na.rm = na.rm)
      return(output)
    }
  )
  
}

# script end;