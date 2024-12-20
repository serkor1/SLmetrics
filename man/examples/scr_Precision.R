# 1) recode Iris
# to binary classification
# problem
iris$species_num <- as.numeric(
  iris$Species == "virginica"
)

# 2) fit the logistic
# regression
model <- glm(
  formula = species_num ~ Sepal.Length + Sepal.Width,
  data    = iris,
  family  = binomial(
    link = "logit"
  )
)

# 3) generate predicted
# classes
predicted <- factor(
  as.numeric(
    predict(model, type = "response") > 0.5
  ),
  levels = c(1,0),
  labels = c("Virginica", "Others")
)

# 3.1) generate actual
# classes
actual <- factor(
  x = iris$species_num,
  levels = c(1,0),
  labels = c("Virginica", "Others")
)

# 4) evaluate class-wise performance
# using Precision

# 4.1) unweighted Precision
precision(
  actual    = actual,
  predicted = predicted
)

# 4.2) weighted Precision
weighted.precision(
  actual    = actual,
  predicted = predicted,
  w         = iris$Petal.Length/mean(iris$Petal.Length)
)

# 5) evaluate overall performance
# using micro-averaged Precision
cat(
  "Micro-averaged Precision", precision(
    actual    = actual,
    predicted = predicted,
    micro     = TRUE
  ),
  "Micro-averaged Precision (weighted)", weighted.precision(
    actual    = actual,
    predicted = predicted,
    w         = iris$Petal.Length/mean(iris$Petal.Length),
    micro     = TRUE
  ),
  sep = "\n"
)
