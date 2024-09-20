# 1) assume that actual
# and predicted are class labels
# from some model
actual <- factor(
  x = sample(
    x = 1:4,
    size = 1e3,
    replace = TRUE
  ),
  levels = c(1:4),
  labels = letters[1:4]
)

# 1.2) predicted
# values
predicted <- factor(
  x = sample(
    x = 1:4,
    size = 1e3,
    replace = TRUE
  ),
  levels = c(1:4),
  labels = letters[1:4]
)


# 2) generate confusion
# matrix
cmatrix(
  actual,
  predicted
)
