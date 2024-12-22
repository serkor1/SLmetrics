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
# performance using Mean Percentage Error (MPE)
cat(
  "Mean Percentage Error", mpe(
    actual    = actual,
    predicted = predicted,
  ),
  "Mean Percentage Error (weighted)", weighted.mpe(
    actual    = actual,
    predicted = predicted,
    w         = mtcars$mpg/mean(mtcars$mpg)
  ),
  sep = "\n"
)
