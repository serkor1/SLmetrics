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
response <-predict(model, type = "response")

# 4) generate reciever
# operator characteristics
roc <- prROC(
  actual   = iris$Species,
  response = response
)


# 5) plot by species
plot(roc)


# 6) provide custom
# threholds
roc <- prROC(
  actual     = iris$Species,
  response   = response,
  thresholds = seq(0, 1, length.out = 4)
)


# 5) plot by species
plot(roc)
