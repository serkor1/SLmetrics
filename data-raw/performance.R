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
classes <- c(2)

# 1.2) sample size
N       <- seq(from = 100, by = 100, length.out = 200)

# 2) conduct test
# on confusion matrix
confusion_matrix_performance <- list()
i <- 1
for (k in classes) {
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
        `{mlr3measures}` = mlr3measures::confusion_matrix(predicted, actual,positive = "a"),
        times = 1000
      )
    )[
      ,
      .(
        sample_size = n,
        classes     = k,
        median      = median(
          time
        )
      )
      ,
      by = .(
        expr
      )
    ]

    confusion_matrix_performance[[i]] <- test_results

    i <<- i + 1

  }
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
      )
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
  confusion_matrix = data.table::rbindlist(confusion_matrix_performance),
  rmse             = data.table::rbindlist(rmse_performance)
)


usethis::use_data(
  DT,
  internal = TRUE,
  overwrite = TRUE
)

# script end;

