# 1) assume that actual
# and predicted are class labels
# from some model
actual <- factor(
  x = sample(
    x = 1:3,
    size = 10,
    replace = TRUE,
    prob = c(0.1,0.1,0.8)
  ),
  levels = c(1:4),
  labels = letters[1:4]
)

# 1.2) predicted
# values
predicted <- factor(
  x = sample(
    x = 1:4,
    size = 10,
    replace = TRUE,
    prob = c(0.1,0.1,0.8,0)
  ),
  levels = c(1:4),
  labels = letters[1:4]
)

# 2) evaluate the
# performance of all classes
jaccard(
  actual    = actual,
  predicted = predicted
)

# 3) evaluate the
# overall performance
# with micro averaging
jaccard(
  actual    = actual,
  predicted = predicted,
  aggregate = TRUE
)

# 4) evaluate the
# overall performance
# with macro averaging
mean(
  jaccard(
    actual    = actual,
    predicted = predicted,
    aggregate = FALSE
  )
)
