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


# 2) calculate
# the ccc measure
ccc(
  actual     = actual,
  predicted  = predicted,
  correction = TRUE
)

# 3) calculate
# the weighted ccc
w <- rbeta(
  n = 1e3,
  shape1 = 10,
  shape2 = 2
)

wccc(
  actual     = actual,
  predicted  = predicted,
  w          = w,
  correction = TRUE
)
