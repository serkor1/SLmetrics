# 1) Define actual
# and observed probabilities

# 1.1) actual probabilies
pk <- matrix(
  cbind(1/2, 1/2),
  ncol = 2
)

# 1.2) observed (estimated) probabilites
qk <- matrix(
  cbind(9/10, 1/10), 
  ncol = 2
)

# 2) calculate
# Entropy
cat(
  "Entropy", entropy(
    pk
  ),
  "Relative Entropy", relative.entropy(
    pk,
    qk
  ),
  "Cross Entropy", cross.entropy(
    pk,
    qk
  ),
  sep = "\n"
)