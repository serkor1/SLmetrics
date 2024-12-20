# 1) fit a linear
# regression
model <- lm(
  mpg ~ .,
  data = mtcars
)

# 1.1) define actual
# and predicted values
# to measure in-sample performance
actual    <- mtcars$mpg
predicted <- fitted(model)

# 2) calculate performance
# using R squared adjusted and
# unadjused for features
cat(
  "Rsq", rsq(
    actual    = actual,
    predicted = fitted(model)
  ),
  "Rsq (Adjusted)", rsq(
    actual    = actual,
    predicted = fitted(model),
    k = ncol(model.matrix(model)) - 1
  ),
  sep = "\n"
)
