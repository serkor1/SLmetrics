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


# 2) calculate
# the rmse measure
rmse(
  actual     = actual,
  predicted  = predicted
)

# 3) calculate
# the weighted rmse
# using arbtrary weights
w <- rbeta(
  n = 1e3,
  shape1 = 10,
  shape2 = 2
)

wrmse(
  actual     = actual,
  predicted  = predicted,
  w          = w
)
