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
# using F1-score

# 4.1) unweighted F1-score
fbeta(
  actual    = actual,
  predicted = predicted,
  beta      = 1
)

# 4.2) weighted F1-score
weighted.fbeta(
  actual    = actual,
  predicted = predicted,
  w         = iris$Petal.Length/mean(iris$Petal.Length),
  beta      = 1
)

# 5) evaluate overall performance
# using micro-averaged F1-score
cat(
  "Micro-averaged F1-score", fbeta(
    actual    = actual,
    predicted = predicted,
    beta      = 1,
    micro     = TRUE
  ),
  "Micro-averaged F1-score (weighted)", weighted.fbeta(
    actual    = actual,
    predicted = predicted,
    w         = iris$Petal.Length/mean(iris$Petal.Length),
    beta      = 1,
    micro     = TRUE
  ),
  sep = "\n"
)
