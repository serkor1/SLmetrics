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
classes <- c(2, 4, 8, 12)

# 1.2) sample size
N       <- c(1e1, 1e2, 1e3, 1e4, 1e5, 1e6)

# 2) conduct test
# on confusion matrix
confusion_matrix_performance <- list()
i <- 1
for (k in classes) {
  for (n in N) {

    # 2.1) create available
    # factors
    actual <- create_factor(k = k, n = n)
    predicted <- create_factor(k = k, n = n)

    # 2.1) evaluate
    # performance
    test_results <- data.table::as.data.table(
      microbenchmark::microbenchmark(
        `{SLmetrics}` = SLmetrics::cmatrix(actual, predicted),
        `{yardstick}` = yardstick::conf_mat(table(actual, predicted)),
        `{MLmetrics}` = MLmetrics::ConfusionMatrix(predicted, actual),
        times = 1000
      )
    )[
      ,
      .(
        sample_size = n,
        classes     = k,
        mean        = mean(
          time
        ),
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

RMSE <- function(actual, predicted, w = NULL) {

  if (!is.null(w)) {

    SLmetrics::wrmse(
      actual,
      predicted,
      w
    )

  } else {

    SLmetrics::rmse(
      actual,
      predicted
    )

  }

}

i <- 1
for (n in N) {

  # 2.1) create available
  # factors
  actual <- rnorm(n = n)
  predicted <- actual + rnorm(n = n)

  # 2.1) evaluate
  # performance
  test_results <- data.table::as.data.table(
    microbenchmark::microbenchmark(
      `{SLmetrics}` = RMSE(actual, predicted),
      `{yardstick}` = yardstick::rmse_vec(actual, predicted),
      `{MLmetrics}` = MLmetrics::RMSE(predicted, actual),
      times = 1000
    )
  )[
    ,
    .(
      sample_size = n,
      mean        = mean(
        time
      ),
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

