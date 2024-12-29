# script: Performance
# date: 2024-10-05
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Make a performance evaluation
# against {MLmetrics}, {mlr3measures} and {yardstick}
# script start;

# 0) prelims
rm(list = ls()); gc(); source("tests/testthat/setup.R")

# 1) setup testing
# grounds

# 1.1) classes available
k <- c(2)

# 1.2) sample size
N <- seq(from = 2e3, by = 2e3, length.out = 50)

# 2) conduct test
# on confusion matrix
confusion_matrix_performance <- list()
i <- 1
for (n in N) {

  invisible(gc())

  # 2.1) create available
  # factors
  actual <- create_factor(k = k, n = n)
  predicted <- create_factor(k = k, n = n)

  # 2.1) evaluate
  # performance
  test_results <- data.table::as.data.table(
    microbenchmark::microbenchmark(
      `{SLmetrics}`    = SLmetrics::cmatrix(actual, predicted),
      `{yardstick}`    = yardstick::conf_mat(table(actual, predicted)),
      `{MLmetrics}`    = MLmetrics::ConfusionMatrix(predicted, actual),
      `{mlr3measures}` = mlr3measures::confusion_matrix(predicted, actual, positive = "a"),
      times = 1000
    )
  )[
    ,
    .(
      sample_size = n,
      median        = median(
        time
      ),
      measure     = "Confusion Matrix"
    )
    ,
    by = .(
      expr
    )
  ]

  confusion_matrix_performance[[i]] <- test_results

  i <<- i + 1

}

# 2) conduct test
# on RMSE
rmse_performance <- list()

i <- 1
for (n in N) {

  invisible(gc())

  # 2.1) create available
  # factors
  actual <- rnorm(n = n)
  predicted <- actual + rnorm(n = n)

  # 2.1) evaluate
  # performance
  test_results <- data.table::as.data.table(
    microbenchmark::microbenchmark(
      `{SLmetrics}`    = SLmetrics::rmse(actual, predicted),
      `{yardstick}`    = yardstick::rmse_vec(actual, predicted),
      `{MLmetrics}`    = MLmetrics::RMSE(predicted, actual),
      `{mlr3measures}` = mlr3measures::rmse(actual, predicted),
      times = 1000
    )
  )[
    ,
    .(
      sample_size = n,
      median      = median(
        time
      ),
      measure     = "Root Mean Squared Error"
    )
    ,
    by = .(
      expr
    )
  ]

  rmse_performance[[i]] <- test_results

  i <<- i + 1

}

# 3) collect results
# in data.table
DT <- list(
  speed = list(
    confusion_matrix = data.table::rbindlist(confusion_matrix_performance),
    rmse             = data.table::rbindlist(rmse_performance)
  )
)

# 4) test memory usage
memory <- list()

# 4.1) Confusion Matrix
actual    <- create_factor(k = 2, n = 1e7)
predicted <- create_factor(k = 2, n = 1e7)

test_results <- bench::mark(
  `{SLmetrics}`    = SLmetrics::cmatrix(actual, predicted),
  `{yardstick}`    = yardstick::conf_mat(table(actual, predicted)),
  `{MLmetrics}`    = MLmetrics::ConfusionMatrix(predicted, actual),
  `{mlr3measures}` = mlr3measures::confusion_matrix(predicted, actual, positive = "a"),
  check = FALSE,
  iterations = 100
)

memory$confusion_matrix <- test_results

# 4.2) RMSE
actual <- rnorm(n = 1e7)
predicted <- actual + rnorm(n = 1e7)

test_results <- bench::mark(
  `{SLmetrics}`    = SLmetrics::rmse(actual, predicted),
  `{yardstick}`    = yardstick::rmse_vec(actual, predicted),
  `{MLmetrics}`    = MLmetrics::RMSE(predicted, actual),
  `{mlr3measures}` = mlr3measures::rmse(actual, predicted),
   check = FALSE,
   iterations = 100
)

memory$rmse <- test_results

# 4.3) append to list
DT$memory <- memory

# 5) write data for
# internal usage
usethis::use_data(
  DT,
  internal  = TRUE,
  overwrite = TRUE
)

# script end;
