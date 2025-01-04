# script start;

# 1) prelims

# 1.1) clear environment
# and garbage collection
rm(list = ls()); gc();

# 1.2) load DT list
DT <- SLmetrics:::DT

# 2) conduct classification
# tests on 2 x 2 confusion matrix

# 2.1) define test parameters
# that are common
k <- 2 # classes
N <- seq(2e3, by = 2e3, length.out = 50) # sample size

# 2.2) conduct test by
# sample size
results <- data.table::rbindlist(
    lapply(
      X = N, function(n) {

        # 0) garbage collection
        invisible(gc())

        # 1) generate actual
        # and predicted classes
        set.seed(1903)
        actual <- factor(sample(letters[1:k], size = n, replace = TRUE))
        predicted <- factor(sample(letters[1:k], size = n, replace = TRUE))

        # 2) conduct tests with 
        # microbenchmark
        data.table::as.data.table(
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


      }
  )
)

# 3) store data in 
# DT in speed
DT$speed$confusion_matrix <- results

# 3.1) write back
# to DT
usethis::use_data(
  DT,
  internal  = TRUE,
  overwrite = TRUE
)

# script end;


