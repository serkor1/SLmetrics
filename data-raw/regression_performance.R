# script start;

# 1) prelims

# 1.1) clear environment
# and garbage collection
rm(list = ls()); gc();

# 1.2) load DT list
DT <- SLmetrics:::DT

# 2) conduct regression
# tests for RMSE 

# 2.1) define test parameters
# that are common
N <- seq(2e3, by = 2e3, length.out = 50) # sample size

# 2.2) conduct test by
# sample size
results <- data.table::rbindlist(
  lapply(
    X = N, function(n) {

      # 0) garbage collection
      invisible(gc())

      # 1) generate actual
      # and predicted values
      set.seed(1903)
      actual <- rnorm(n = n)
      predicted <- actual + rnorm(n = n)

      # 2) conduct tests with 
      # microbenchmark
      data.table::as.data.table(
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

    }
  )
)

# 3) store data in 
# DT in speed
DT$speed$rmse <- results

# 3.1) write back
# to DT
usethis::use_data(
  DT,
  internal  = TRUE,
  overwrite = TRUE
)

# script end;