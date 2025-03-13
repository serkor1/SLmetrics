# 1) generate a 4x4 matrix
# with random values to be sorted
set.seed(1903)
X <- matrix(
  data = cbind(sample(16:1)),
  nrow = 4
)

# 2) sort matrix
# in decreasing order
presort(X)

# 3) get indices 
# for sorted matrix
preorder(X)