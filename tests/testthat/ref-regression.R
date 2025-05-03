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

# Reference Concordance Correlation Coefficient
ref_ccc <- function(actual, predicted, w = NULL, correction = FALSE) {

  actual    <- as.numeric(actual)
  predicted <- as.numeric(predicted)
  
  if (is.null(w)) {
    w <- rep(1, length(actual))
  } else {
    w <- as.numeric(w)
  }
  
  data <- cbind(actual = actual, predicted = predicted)
  cov_matrix <- stats::cov.wt(
    x = data,
    wt = w,
    cor = FALSE,
    center = TRUE,
    method = "unbiased"
  )
  
  actual_mean <- weighted.mean(actual, w = w)
  predicted_mean <- weighted.mean(predicted, w = w)
  actual_variance <- cov_matrix$cov[1, 1]
  predicted_variance <- cov_matrix$cov[2, 2]
  covariance <- cov_matrix$cov[1, 2]
  
  if (correction) {
    n <- sum(w) 
    actual_variance <- actual_variance * (n - 1) / n
    predicted_variance <- predicted_variance * (n - 1) / n
    covariance <- covariance * (n - 1) / n
  }
  
  numerator <- 2 * covariance
  denominator <- actual_variance + predicted_variance + (actual_mean - predicted_mean)^2
  ccc_value <- numerator / denominator
  
  return(ccc_value)
}


# Reference Root Relative Squared Error
py_rrse <- function(
  actual,
  predicted,
  w = NULL
) {

  if (is.null(w)) {
    w <- rep(1, length(actual))
  }

  sqrt(
    sum(w * (actual - predicted)^2) / 
    sum(w*( actual - weighted.mean(actual, w = w))^2))

}

# Reference Relative Absolute Error
py_rae <- function(
  actual,
  predicted,
  w = NULL) {
  
  if (is.null(w)) {
    w <- rep(1, length(actual))
  }
  
    sum(w * abs(actual - predicted)) / sum( w * abs(actual - weighted.mean(actual, w = w)))
}

# Reference Mean Percentage Error
py_mpe <- function(
  predicted, 
  actual, 
  w = NULL) {
  
  if (is.null(w)) {
    w <- rep(1, length(actual))
  }
  
  error <- (actual - predicted) / actual
  weighted_mpe <- sum(w * error) / sum(w)
  
  weighted_mpe
}

# Reference Relative Root Mean Squared Error
ref_rrmse <- function(actual, predicted, w = NULL, normalization = 0) {

  weighted_quantile <- function(values, weights, alpha) {
    # Pair values with weights
    data <- data.frame(values = values, weights = weights)
    
    # Sort by values
    data <- data[order(data$values), ]
    
    # Compute total weight
    total_weight <- sum(data$weights)
    
    # Compute target cumulative weight
    target_weight <- alpha * total_weight
    
    # Initialize cumulative weight
    cumulative_weight <- 0.0
    
    # Variables to store the lower and upper bounds
    lower <- 0.0
    upper <- 0.0
    lower_set <- FALSE
    
    # Iterate through the sorted data
    for (i in seq_len(nrow(data))) {
      cumulative_weight <- cumulative_weight + data$weights[i]
      
      if (!lower_set && cumulative_weight >= target_weight) {
        lower <- data$values[i]
        lower_set <- TRUE
      }
      
      if (cumulative_weight >= target_weight) {
        upper <- data$values[i]
        break
      }
    }
    
    # Interpolation
    return(lower + (upper - lower) * ((target_weight - (cumulative_weight - data$weights[i])) / total_weight))
  }
  
  

  # Calculate RMSE
  RMSE <- sqrt(weighted.mean(
    (actual - predicted)^2,
    w = if (is.null(w)) rep(1, length(actual)) else w
  ))

  denominator <- 1
  if (normalization == 0) {
    denominator <- weighted.mean(
      actual,
      w = if (is.null(w)) rep(1, length(actual)) else w
    )
  } 

  if (normalization == 1) {
    denominator <- if (is.null(w)) diff(range(actual)) else diff(range(actual))
  }

  
  
  if (normalization == 2) {
    if (is.null(w)) {
      denominator <- IQR(
        actual,
        type = 5
      )
    } else {
      denominator <- weighted_quantile(actual, weights = w, alpha = 0.75) - weighted_quantile(actual, weights = w, alpha = 0.25)
    }
    
  }

  RMSE / denominator

}

# Reference Mean Arctangent Absolute Error
ref_maape <- function(
  actual, 
  predicted, 
  w = NULL) {
    weighted.mean(
      x = atan( abs( (actual - predicted) / actual ) ),
      w = if (!is.null(w)) w else rep(1, times = length(actual))
    )
}

# Reference Geometric Mean Squared Error
ref_gmse <- function(
  actual, 
  predicted, 
  w = NULL) {
  exp(
    weighted.mean(
      x = log( (actual - predicted) * (actual - predicted) ),
      w = if (!is.null(w)) w else rep(1, times = length(actual))
    )
  )
}

# script end;
