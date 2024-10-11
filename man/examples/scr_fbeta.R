# 1) recode Iris
# to binary classification
# problem
iris$Species <- factor(
  x = as.numeric(
    iris$Species == "virginica"
  ),
  levels = c(1,0),
  labels = c("virginica", "others")
)

# 2) fit the logistic
# regression
model <- glm(
  formula = Species ~ Sepal.Length + Sepal.Width,
  data    = iris,
  family = binomial(
    link = "logit"
  )
)

# 3) generate predicted
# classes
predicted <- as.factor(
  ifelse(
    predict(model, type = "response") > 0.5,
    yes = "virginica",
    no  = "others"
  )
)

# 4) class-wise f1
# score
fbeta(
  actual    = iris$Species,
  predicted = predicted
)

# 4.1) micro-averaged F1 score
fbeta(
  actual    = iris$Species,
  predicted = predicted,
  micro = TRUE
)

# 4.2 macro-averaged F1 score
fbeta(
  actual    = iris$Species,
  predicted = predicted,
  micro     = FALSE
)
