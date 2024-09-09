# 1) assume that actual
# and predicted are class labels
# from some model
actual <- sample(
  x = letters[1:3],
  size = 100,
  replace = TRUE,
  prob = c(0.2,0.2,0.6)
)

predicted <- sample(
  x = letters[1:3],
  size = 100,
  replace = TRUE,
  prob = c(0.2,0.2,0.6)
)

# 1.1) convert to factor
# variable
actual <- factor(
  x = actual,
  levels = letters[1:3]
)

predicted <- factor(
  x = predicted,
  levels = letters[1:3]
)


# 2) evaluate the
# performance of all classes
recall(
  actual    = actual,
  predicted = predicted
)

# 3) evaluate the
# overall performance
# with micro averaging
recall(
  actual    = actual,
  predicted = predicted,
  aggregate = TRUE
)

# 4) evaluate the
# overall performance
# with macro averaging
mean(
  recall(
    actual    = actual,
    predicted = predicted,
    aggregate = FALSE
  )
)
