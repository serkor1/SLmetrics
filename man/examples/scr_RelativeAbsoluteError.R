# 1) fit a linear
# regression
model <- lm(
  mpg ~ .,
  data = mtcars
)

# 1.1) define actual
# and predicted values
# to measure performance
actual    <- mtcars$mpg
predicted <- fitted(model)

# 2) evaluate in-sample model
# performance using Relative Absolute Error (RAE)
cat(
  "Relative Absolute Error", rae(
    actual    = actual,
    predicted = predicted,
  ),
  "Relative Absolute Error (weighted)", weighted.rae(
    actual    = actual,
    predicted = predicted,
    w         = mtcars$mpg/mean(mtcars$mpg)
  ),
  sep = "\n"
)
