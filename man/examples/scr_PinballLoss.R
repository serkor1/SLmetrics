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
# performance using Pinball Loss
cat(
  "Pinball Loss", pinball(
    actual    = actual,
    predicted = predicted,
  ),
  "Pinball Loss (weighted)", weighted.pinball(
    actual    = actual,
    predicted = predicted,
    w         = mtcars$mpg/mean(mtcars$mpg)
  ),
  sep = "\n"
)
