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

# 2) calculate the huber loss
# with delta 0.5
huberloss(
  actual = actual,
  predicted = predicted,
  delta = 0.5
)

# 3) caclulate weighted
# huber loss
w <- rbeta(
  n = 1e3,
  shape1 = 10,
  shape2 = 2
)

huberloss(
  actual = actual,
  predicted = predicted,
  delta = 0.5,
  w     = w
)
