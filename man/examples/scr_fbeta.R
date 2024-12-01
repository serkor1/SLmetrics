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


# 4) class-wise f1
# score
fbeta(
  actual    = actual,
  predicted = predicted
)

# 4.1) micro-averaged F1 score
fbeta(
  actual    = actual,
  predicted = predicted,
  micro = TRUE
)

# 4.2 macro-averaged F1 score
fbeta(
  actual    = actual,
  predicted = predicted,
  micro     = FALSE
)
