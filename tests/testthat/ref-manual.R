# script: Manual Calculations of
# measures not found in Python
# date: 2024-10-07
# author: Serkan Korkmaz, serkor1@duck.com
# objective: These function manually
# calculates the metrics and serves as a reference
# for future changes in the package.
#
# They are named py_foo because it
# was convienient.
# script start;

# False Discovery Rate
py_fdr <- function(
    actual,
    predicted,
    average = NULL,
    na.rm = TRUE) {

  # 1) Construct matrix
  conf_mat <- table(
    actual,
    predicted
  )

  # 2) Construct elements
  # of the calculation
  FP <- colSums(conf_mat) - diag(conf_mat)
  PP <- colSums(conf_mat)

  output <-  FP / PP

  # 2) calculate values
  if (!is.null(average)) {

    average <- as.logical(average == "micro")

    if (average) {

      output <-  sum(FP, na.rm = TRUE) / sum(PP, na.rm = TRUE)

    } else {

      if (!na.rm) {

        output[!is.finite(output)] <- 0

      }

      output <- mean(
        output,
        na.rm = na.rm
      )

    }

  }

  return(
    output
  )


}

py_fpr <- function(actual, predicted, average = NULL, na.rm = TRUE) {
  # Construct confusion matrix
  conf_mat <- table(actual, predicted)

  # Calculate False Positives and True Negatives per class
  FP <- colSums(conf_mat) - diag(conf_mat)
  TN <- sum(conf_mat) - rowSums(conf_mat) - colSums(conf_mat) + diag(conf_mat)

  # Calculate False Positive Rate per class
  fpr_class <- FP / (FP + TN)

  # If averaging is requested
  if (!is.null(average)) {
    if (average == "micro") {
      return(sum(FP, na.rm = TRUE) / (sum(FP, na.rm = TRUE) + sum(TN, na.rm = TRUE)))
    } else {
      if (!na.rm) {
        fpr_class[!is.finite(fpr_class)] <- 0
      }
      return(mean(fpr_class, na.rm = na.rm))
    }
  }

  return(fpr_class)
}

py_npv <- function(actual, predicted, average = NULL, na.rm = TRUE) {
  # Construct confusion matrix
  conf_mat <- table(actual, predicted)

  # Calculate True Negatives and False Negatives per class
  TN <- sum(conf_mat) - rowSums(conf_mat) - colSums(conf_mat) + diag(conf_mat)
  FN <- rowSums(conf_mat) - diag(conf_mat)

  # Calculate Negative Predictive Value per class
  npv_class <- TN / (TN + FN)

  # If averaging is requested
  if (!is.null(average)) {
    if (average == "micro") {
      return(sum(TN, na.rm = TRUE) / (sum(TN, na.rm = TRUE) + sum(FN, na.rm = TRUE)))
    } else {
      if (!na.rm) {
        npv_class[!is.finite(npv_class)] <- 0
      }
      return(mean(npv_class, na.rm = na.rm))
    }
  }

  return(npv_class)
}

py_fer <- function(actual, predicted, average = NULL, na.rm = TRUE) {
  # Construct confusion matrix
  conf_mat <- table(actual, predicted)

  # Calculate False Negatives and True Negatives per class
  FN <- rowSums(conf_mat) - diag(conf_mat)
  TN <- sum(conf_mat) - rowSums(conf_mat) - colSums(conf_mat) + diag(conf_mat)

  # Calculate False Omission Rate per class
  for_class <- FN / (TN + FN)

  # If averaging is requested
  if (!is.null(average)) {
    if (average == "micro") {
      return(sum(FN, na.rm = TRUE) / (sum(TN, na.rm = TRUE) + sum(FN, na.rm = TRUE)))
    } else {
      if (!na.rm) {
        for_class[!is.finite(for_class)] <- 0
      }
      return(mean(for_class, na.rm = na.rm))
    }
  }

  return(for_class)
}

py_plr <- function(actual, predicted, average = NULL, na.rm = TRUE) {
  # Construct confusion matrix
  conf_mat <- table(actual, predicted)

  # Calculate True Positives, False Positives, False Negatives, and True Negatives
  TP <- diag(conf_mat)
  FP <- colSums(conf_mat) - TP
  FN <- rowSums(conf_mat) - TP
  TN <- sum(conf_mat) - rowSums(conf_mat) - colSums(conf_mat) + TP

  # Calculate TPR and FPR per class
  TPR <- TP / (TP + FN)
  FPR <- FP / (FP + TN)

  # Calculate Positive Likelihood Ratio per class
  plr_class <- TPR / FPR

  # If averaging is requested
  if (!is.null(average)) {
    if (average == "micro") {
      # Micro-average
      overall_tpr <- sum(TP, na.rm = TRUE) / (sum(TP, na.rm = TRUE) + sum(FN, na.rm = TRUE))
      overall_fpr <- sum(FP, na.rm = TRUE) / (sum(FP, na.rm = TRUE) + sum(TN, na.rm = TRUE))
      return(overall_tpr / overall_fpr)
    } else {
      # Handle non-finite values in macro-average case
      if (!na.rm) {
        plr_class[!is.finite(plr_class)] <- 0
      }
      return(mean(plr_class, na.rm = na.rm))
    }
  }

  return(plr_class)
}

py_nlr <- function(actual, predicted, average = NULL, na.rm = TRUE) {
  # Construct confusion matrix
  conf_mat <- table(actual, predicted)

  # Calculate True Positives, False Positives, False Negatives, and True Negatives
  TP <- diag(conf_mat)
  FP <- colSums(conf_mat) - TP
  FN <- rowSums(conf_mat) - TP
  TN <- sum(conf_mat) - rowSums(conf_mat) - colSums(conf_mat) + TP

  # Calculate TPR and TNR per class
  TPR <- TP / (TP + FN)
  TNR <- TN / (TN + FP)

  # Calculate Negative Likelihood Ratio per class
  nlr_class <- (1 - TPR) / TNR

  # If averaging is requested
  if (!is.null(average)) {
    if (average == "micro") {
      # Micro-average
      overall_tpr <- sum(TP, na.rm = TRUE) / (sum(TP, na.rm = TRUE) + sum(FN, na.rm = TRUE))
      overall_tnr <- sum(TN, na.rm = TRUE) / (sum(TN, na.rm = TRUE) + sum(FP, na.rm = TRUE))
      return((1 - overall_tpr) / overall_tnr)
    } else {
      # Handle non-finite values in macro-average case
      if (!na.rm) {
        nlr_class[!is.finite(nlr_class)] <- 0
      }
      return(mean(nlr_class, na.rm = na.rm))
    }
  }

  return(nlr_class)
}

py_dor <- function(actual, predicted, average = NULL, na.rm = TRUE) {
  # Construct confusion matrix
  conf_mat <- table(actual, predicted)

  # Calculate True Positives, False Positives, False Negatives, and True Negatives
  TP <- diag(conf_mat)
  FP <- colSums(conf_mat) - TP
  FN <- rowSums(conf_mat) - TP
  TN <- sum(conf_mat) - rowSums(conf_mat) - colSums(conf_mat) + TP

  # Calculate Diagnostic Odds Ratio per class
  dor_class <- (TP * TN) / (FP * FN)

  # If averaging is requested
  if (!is.null(average)) {
    if (average == "micro") {
      # Micro-average
      overall_tp <- sum(TP, na.rm = TRUE)
      overall_tn <- sum(TN, na.rm = TRUE)
      overall_fp <- sum(FP, na.rm = TRUE)
      overall_fn <- sum(FN, na.rm = TRUE)
      return((overall_tp * overall_tn) / (overall_fp * overall_fn))
    } else {
      # Handle non-finite values in macro-average case
      if (!na.rm) {
        dor_class[!is.finite(dor_class)] <- 0
      }
      return(mean(dor_class, na.rm = na.rm))
    }
  }

  return(dor_class)
}


ref_ROC <- function(actual, response, thresholds) {

  n_thresholds <- length(thresholds)
  k <- n_levels <- length(levels(actual))
  total_rows <- n_thresholds * n_levels

  output <- data.frame(
    threshold = rep(thresholds, each = n_levels),
    level = rep(1:n_levels, times = n_thresholds),
    label = rep(letters[1:n_levels], times = n_thresholds),
    fpr = numeric(total_rows),
    tpr = numeric(total_rows),
    stringsAsFactors = FALSE
  )

  for (i in 1:n_levels) {

    for (j in 1:n_thresholds) {
      threshold_val <- thresholds[j]

      predicted <- factor(
        x = ifelse(
          response >= threshold_val,
          yes = i, # was i
          no  = (k+1) - i  # was (k+1) - i
        ),
        labels = letters[1:k],
        levels = 1:k
      )


      row_index <- (j - 1) * n_levels + i
      output$fpr[row_index] <- SLmetrics::fpr(actual = actual, predicted = predicted)[i] # was i
      output$tpr[row_index] <- SLmetrics::tpr(actual = actual, predicted = predicted)[i] # was i
    }
  }

  output <- output[order(output$level, -output$threshold),]
  rownames(output) <- NULL

  output
}

ref_prROC <- function(actual, response, thresholds) {

  n_thresholds <- length(thresholds)
  k <- n_levels <- length(levels(actual))
  total_rows <- n_thresholds * n_levels

  output <- data.frame(
    threshold = rep(thresholds, each = n_levels),
    level = rep(1:n_levels, times = n_thresholds),
    label = rep(letters[1:n_levels], times = n_thresholds),
    precision = numeric(total_rows),
    recall = numeric(total_rows),
    stringsAsFactors = FALSE
  )

  for (i in 1:n_levels) {

    for (j in 1:n_thresholds) {
      threshold_val <- thresholds[j]

      predicted <- factor(
        x = ifelse(
          response >= threshold_val,
          yes = i, # was i
          no  = (k+1) - i  # was (k+1) - i
        ),
        labels = letters[1:k],
        levels = 1:k
      )


      row_index <- (j - 1) * n_levels + i
      output$precision[row_index] <- SLmetrics::precision(actual = actual, predicted = predicted)[i] # was i
      output$recall[row_index] <- SLmetrics::recall(actual = actual, predicted = predicted)[i] # was i
    }
  }

  output <- output[order(output$level, -output$threshold),]
  rownames(output) <- NULL

  numeric_cols <- sapply(output, is.numeric)
  output[numeric_cols] <- lapply(output[numeric_cols], function(col) {
    col[is.nan(col)] <- 0
    col
  })

  output

}


# script end;
