# 1) assume that actual
# and predicted are values
# from a model
actual <- rnorm(
  n = 1e3,
  mean = 10
)

predicted <- actual + rnorm(
  n = 1e3,
  mean = 10
)

# 2) calculate the smape
smape(
  actual = actual,
  predicted = predicted
)

# 3) caclulate weighted
# huber loss
w <- rbeta(
  n = 1e3,
  shape1 = 10,
  shape2 = 2
)

wsmape(
  actual = actual,
  predicted = predicted,
  w     = w
)
