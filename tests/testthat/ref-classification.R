
# Reference Recall
ref_recall <- function(
  actual,
  predicted,
  w = NULL ,
  micro = NULL,
  na.rm = TRUE) {
  
  generalized_metric(
    actual      = actual,
    predicted   = predicted,
    w           = w,
    micro       = micro,
    na.rm       = na.rm,
    metric_expr = TP / (TP + FN)
  )
}

# Reference Specificity
ref_specificity <- function(
  actual,
  predicted,
  w = NULL,
  micro = NULL,
  na.rm = TRUE) {
  
  generalized_metric(
    actual      = actual,
    predicted   = predicted,
    w           = w,
    micro       = micro,
    na.rm       = na.rm,
    metric_expr = TN / (TN + FP)
  )
}

# Reference False Discovery Rate
ref_fdr <- function(
  actual,
  predicted,
  w = NULL,
  micro = NULL,
  na.rm = TRUE) {
  
  generalized_metric(
    actual      = actual,
    predicted   = predicted,
    w           = w,
    micro       = micro,
    na.rm       = na.rm,
    metric_expr = FP / (FP + TP)
  )
}

# Reference False Positive Rate
ref_fpr <- function(
  actual,
  predicted,
  w = NULL,
  micro = NULL,
  na.rm = TRUE) {
  
  generalized_metric(
    actual      = actual,
    predicted   = predicted,
    w           = w,
    micro       = micro,
    na.rm       = na.rm,
    metric_expr = FP / (FP + TN)
  )
}

# Reference Negative Predictive Value
ref_npv <- function(
  actual,
  predicted,
  w = NULL,
  micro = NULL,
  na.rm = TRUE) {
  
  generalized_metric(
    actual      = actual,
    predicted   = predicted,
    w           = w,
    micro       = micro,
    na.rm       = na.rm,
    metric_expr = TN / (TN + FN)
  )
}

# Reference False Omission Rate
ref_fer <- function(
  actual,
  predicted,
  w = NULL,
  micro = NULL,
  na.rm = TRUE) {
  
  generalized_metric(
    actual      = actual,
    predicted   = predicted,
    w           = w,
    micro       = micro,
    na.rm       = na.rm,
    metric_expr = FN / (TN + FN)
  )
}

# Reference Positive Likelihood Ratio
ref_plr <- function(
  actual,
  predicted,
  w = NULL,
  micro = NULL,
  na.rm = TRUE) {
  
  generalized_metric(
    actual      = actual,
    predicted   = predicted,
    w           = w,
    micro       = micro,
    na.rm       = na.rm,
    metric_expr = (TP / (TP + FN)) / (FP / (FP + TN))
  )
}

# Reference Negative Likelihood Ratio
ref_nlr <- function(
  actual,
  predicted,
  w = NULL,
  micro = NULL,
  na.rm = TRUE) {
  
  generalized_metric(
    actual      = actual,
    predicted   = predicted,
    w           = w,
    micro       = micro,
    na.rm       = na.rm,
    metric_expr = (1 - (TP / (TP + FN))) / (TN / (TN + FP))
  )
}

# Reference Diagnostic Odds Ratio
ref_dor <- function(
  actual,
  predicted,
  w = NULL,
  micro = NULL,
  na.rm = TRUE) {
  
  generalized_metric(
    actual      = actual,
    predicted   = predicted,
    w           = w,
    micro       = micro,
    na.rm       = na.rm,
    metric_expr = (TP * TN) / (FP * FN)
  )
}

ref_ROC <-function(actual, response, thresholds = NULL) {

  n_levels <- length(levels(actual))

  grid <- expand.grid(
    threshold = if (is.null(thresholds)) response else thresholds,
    level = 1:n_levels
  )

  fpr_list <- numeric(nrow(grid))
  tpr_list <- numeric(nrow(grid))

  for (i in seq_len(nrow(grid))) {
    threshold <- grid$threshold[i]
    level <- grid$level[i]

    predicted <- factor(
      x = ifelse(
        response >= threshold,
        yes = level,
        no = (n_levels + 1) - level
      ),
      labels = letters[1:n_levels],
      levels = 1:n_levels
    )

    fpr_list[i] <- generalized_metric(
      actual = actual,
      predicted = predicted,
      metric_expr = FP / (FP + TN)
    )[level]

    tpr_list[i] <- generalized_metric(
      actual = actual,
      predicted = predicted,
      metric_expr = TP / (TP + FN)
    )[level]
  }

  # Create the output data frame
  output <- data.frame(
    threshold = grid$threshold,
    level = grid$level,
    label = letters[grid$level],
    fpr = fpr_list,
    tpr = tpr_list,
    stringsAsFactors = FALSE
  )

  # Sort the output
  output <- output[order(output$level, -output$threshold), ]
  rownames(output) <- NULL

  output
}


ref_prROC <- function(
  actual, 
  response, 
  thresholds = NULL) {

  n_levels <- length(levels(actual))

  # Generate all combinations of thresholds and levels
  grid <- expand.grid(
    threshold = if (is.null(thresholds)) response else thresholds,
    level = 1:n_levels
  )

  # Compute predictions, precision, and recall for each combination
  precision_list <- numeric(nrow(grid))
  recall_list <- numeric(nrow(grid))

  for (i in seq_len(nrow(grid))) {
    threshold <- grid$threshold[i]
    level <- grid$level[i]

    predicted <- factor(
      x = ifelse(
        response >= threshold,
        yes = level,
        no = (n_levels + 1) - level
      ),
      labels = letters[1:n_levels],
      levels = 1:n_levels
    )

    precision_list[i] <- generalized_metric(
      actual = actual,
      predicted = predicted,
      metric_expr = TP / (TP + FP)
    )[level]

    recall_list[i] <- generalized_metric(
      actual = actual,
      predicted = predicted,
      metric_expr = TP / (TP + FN)
    )[level]
  }

  # Create the output data frame
  output <- data.frame(
    threshold = grid$threshold,
    level = grid$level,
    label = letters[grid$level],
    precision = precision_list,
    recall = recall_list,
    stringsAsFactors = FALSE
  )

  # Sort the output
  output <- output[order(output$level, -output$threshold), ]
  rownames(output) <- NULL

  # Replace NaN with 0 in numeric columns
  numeric_cols <- sapply(output, is.numeric)
  output[numeric_cols] <- lapply(output[numeric_cols], function(col) {
    col[is.nan(col)] <- 0
    col
  })

  output
}