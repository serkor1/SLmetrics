# Reference Confusion Matrix
py_cmatrix <- function(
    actual,
    predicted,
    w = NULL) {
    if (is.null(w)) {
        w <- rep(1, length(actual))
    }

    cm <- tapply(
        w,
        INDEX = list(actual, predicted),
        FUN = sum,
        default = 0
    )

    cm <- as.matrix(cm)

    cm[is.na(cm)] <- 0

    return(cm)
}

# Reference fbeta-score
ref_fbeta <- function(
    actual,
    predicted,
    w = NULL,
    estimator = 0,
    na.rm = TRUE,
    beta = 1) {
    generalized_metric(
        actual      = actual,
        predicted   = predicted,
        w           = w,
        estimator   = estimator,
        na.rm       = na.rm,
        metric_expr = ((1 + beta^2) * TP) / (((1 + beta^2) * TP) + (beta^2 * FN) + FP),
        beta        = beta
    )
}

# Reference Precision
ref_precision <- function(
    actual,
    predicted,
    w = NULL,
    estimator = 0,
    na.rm = TRUE) {
    generalized_metric(
        actual      = actual,
        predicted   = predicted,
        w           = w,
        estimator   = estimator,
        na.rm       = na.rm,
        metric_expr = TP / (TP + FP)
    )
}


# Reference Recall
ref_recall <- function(
    actual,
    predicted,
    w = NULL,
    estimator = 0,
    na.rm = TRUE) {
    generalized_metric(
        actual      = actual,
        predicted   = predicted,
        w           = w,
        estimator   = estimator,
        na.rm       = na.rm,
        metric_expr = TP / (TP + FN)
    )
}

# Reference Specificity
ref_specificity <- function(
    actual,
    predicted,
    w = NULL,
    estimator = 0,
    na.rm = TRUE) {
    generalized_metric(
        actual      = actual,
        predicted   = predicted,
        w           = w,
        estimator   = estimator,
        na.rm       = na.rm,
        metric_expr = TN / (TN + FP)
    )
}

# Reference False Discovery Rate
ref_fdr <- function(
    actual,
    predicted,
    w = NULL,
    estimator = 0,
    na.rm = TRUE) {
    generalized_metric(
        actual      = actual,
        predicted   = predicted,
        w           = w,
        estimator   = estimator,
        na.rm       = na.rm,
        metric_expr = FP / (FP + TP)
    )
}

# Reference False Positive Rate
ref_fpr <- function(
    actual,
    predicted,
    w = NULL,
    estimator = 0,
    na.rm = TRUE) {
    generalized_metric(
        actual      = actual,
        predicted   = predicted,
        w           = w,
        estimator   = estimator,
        na.rm       = na.rm,
        metric_expr = FP / (FP + TN)
    )
}

# Reference Negative Predictive Value
ref_npv <- function(
    actual,
    predicted,
    w = NULL,
    estimator = 0,
    na.rm = TRUE) {
    generalized_metric(
        actual      = actual,
        predicted   = predicted,
        w           = w,
        estimator   = estimator,
        na.rm       = na.rm,
        metric_expr = TN / (TN + FN)
    )
}

# Reference False Omission Rate
ref_fer <- function(
    actual,
    predicted,
    w = NULL,
    estimator = 0,
    na.rm = TRUE) {
    generalized_metric(
        actual      = actual,
        predicted   = predicted,
        w           = w,
        estimator   = estimator,
        na.rm       = na.rm,
        metric_expr = FN / (TN + FN)
    )
}

# Reference Positive Likelihood Ratio
ref_plr <- function(
    actual,
    predicted,
    w = NULL,
    estimator = 0,
    na.rm = TRUE) {
    generalized_metric(
        actual      = actual,
        predicted   = predicted,
        w           = w,
        estimator   = estimator,
        na.rm       = na.rm,
        metric_expr = (sum(TP) / (sum(TP) + sum(FN))) / (sum(FP) / (sum(FP) + sum(TN)))
    )
}

# Reference Negative Likelihood Ratio
ref_nlr <- function(
    actual,
    predicted,
    w = NULL,
    estimator = 0,
    na.rm = TRUE) {
    generalized_metric(
        actual      = actual,
        predicted   = predicted,
        w           = w,
        estimator   = estimator,
        na.rm       = na.rm,
        metric_expr = (1 - (sum(TP) / (sum(TP) + sum(FN)))) / (sum(TN) / (sum(TN) + sum(FP)))
    )
}

# Reference Diagnostic Odds Ratio
ref_dor <- function(
    actual,
    predicted,
    w = NULL,
    estimator = 0,
    na.rm = TRUE) {
    generalized_metric(
        actual      = actual,
        predicted   = predicted,
        w           = w,
        micro       = NULL,
        na.rm       = na.rm,
        metric_expr = (sum(TP) * sum(TN)) / (sum(FP) * sum(FN))
    )
}

# Reference Fowlkes Mallos Index
# NOTE: This is for weighted version
# only
ref_fmi <- function(
    actual,
    predicted,
    w) {
    conf_mat <- confusion_matrix(actual, predicted, w = w)

    N <- sum(conf_mat)
    tk <- sum(conf_mat^2) - N

    col_sums <- colSums(conf_mat)
    pk <- sum(col_sums^2) - N

    row_sums <- rowSums(conf_mat)
    qk <- sum(row_sums^2) - N

    sqrt((tk / pk) * (tk / qk))
}

ref_ROC <- function(actual, response, thresholds = NULL, w = NULL, estimator = 0) {
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
            actual      = actual,
            predicted   = predicted,
            metric_expr = FP / (FP + TN),
            estimator   = estimator,
            w           = w
        )[level]

        tpr_list[i] <- generalized_metric(
            actual = actual,
            predicted = predicted,
            metric_expr = TP / (TP + FN),
            micro = micro,
            w = w
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

# Reference Poisson LogLoss
ref_poisson_logloss <- function(
    actual,
    response,
    w = NULL,
    normalize = TRUE) {
    eps <- 1e-15
    response <- pmax(response, eps)
    loss_vals <- log(gamma(actual + 1)) + response - actual * log(response)

    if (is.null(w)) {
        # Unweighted
        if (normalize) {
            # Mean of losses
            return(mean(loss_vals))
        } else {
            # Sum of losses
            return(sum(loss_vals))
        }
    } else {
        w <- as.numeric(w)
        weighted_loss <- w * loss_vals

        if (normalize) {
            return(sum(weighted_loss) / sum(w))
        } else {
            return(sum(weighted_loss))
        }
    }
}
