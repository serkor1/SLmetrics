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
# performance using Relative Root Mean Squared Error (RRMSE)
cat(
  "IQR Relative Root Mean Squared Error", rrmse(
    actual        = actual,
    predicted     = predicted,
    normalization = 2
  ),
  "IQR Relative Root Mean Squared Error (weighted)", weighted.rrmse(
    actual        = actual,
    predicted     = predicted,
    w             = mtcars$mpg/mean(mtcars$mpg),
    normalization = 2
  ),
  sep = "\n"
)

