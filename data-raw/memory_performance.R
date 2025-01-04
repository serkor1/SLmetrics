# script start;

# 1) prelims

# 1.1) clear environment
# and garbage collection
rm(list = ls()); gc();

# 1.2) load DT list
DT <- SLmetrics:::DT

# 1.3) common test parameters
# across the script
k <- 2 # classes
N <- 1e7 # sample size
iterations <- 100

# 2) conduct tests
# on classification and regression

# 2.1) confusion matrx
set.seed(1903)
actual <- factor(sample(letters[1:k], size = N, replace = TRUE))
predicted <- factor(sample(letters[1:k], size = N, replace = TRUE))

DT$memory$confusion_matrix <- bench::mark(
  `{SLmetrics}`    = SLmetrics::cmatrix(actual, predicted),
  `{yardstick}`    = yardstick::conf_mat(table(actual, predicted)),
  `{MLmetrics}`    = MLmetrics::ConfusionMatrix(predicted, actual),
  `{mlr3measures}` = mlr3measures::confusion_matrix(predicted, actual, positive = "a"),
  check = FALSE,
  iterations = iterations
)

# 2.2) RMSE
set.seed(1903)
actual <- rnorm(n = N)
predicted <- actual + rnorm(n = N)

DT$memory$confusion_matrix <- bench::mark(
  `{SLmetrics}`    = SLmetrics::rmse(actual, predicted),
  `{yardstick}`    = yardstick::rmse_vec(actual, predicted),
  `{MLmetrics}`    = MLmetrics::RMSE(predicted, actual),
  `{mlr3measures}` = mlr3measures::rmse(actual, predicted),
   check = FALSE,
   iterations = iterations
)

# 3) write back
# to DT
usethis::use_data(
  DT,
  internal  = TRUE,
  overwrite = TRUE
)