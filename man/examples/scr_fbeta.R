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

# 4) F1-score for each
# class
fbeta(
  actual    = iris$Species,
  predicted = predicted
)

# 4.1) micro-averaged F1 score
fbeta(
  actual    = iris$Species,
  predicted = predicted,
  aggregate = TRUE
)

# 4.2 macro-averaged F1 score
mean(
  fbeta(
    actual    = iris$Species,
    predicted = predicted
  )
)

# 5) F-score each class
# with beta 2
fbeta(
  actual    = iris$Species,
  predicted = predicted,
  beta      = 2
)

# 4.1) micro-averaged F-score
# with beta 2
fbeta(
  actual    = iris$Species,
  predicted = predicted,
  beta      = 2,
  aggregate = TRUE
)

# 4.2 macro-averaged F-score
# with beta 2
mean(
  fbeta(
    actual    = iris$Species,
    predicted = predicted,
    beta      = 2
  )
)
