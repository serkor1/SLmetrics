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
# performance using Relative Root Squared Errror (RRSE)
cat(
  "Relative Root Squared Errror", rrse(
    actual    = actual,
    predicted = predicted,
  ),
  "Relative Root Squared Errror (weighted)", weighted.rrse(
    actual    = actual,
    predicted = predicted,
    w         = mtcars$mpg/mean(mtcars$mpg)
  ),
  sep = "\n"
)
