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
response <- predict(model, type = "response")

# 3.1) generate actual
# classes
actual <- factor(
  x = iris$species_num,
  levels = c(1,0),
  labels = c("Virginica", "Others")
)

# 4) generate receiver operator characteristics
# data

# 4.1) calculate residual
# probability and store as matrix
response <- matrix(
  data = cbind(response, 1-response),
  nrow = length(actual)
)

# 4.2) calculate class-wise
# area under the curve
roc.auc(
  actual   = actual,
  response = response 
)

# 4.3) calculate class-wise
# weighted area under the curve
weighted.roc.auc(
  actual   = actual,
  response = response,
  w        = iris$Petal.Length/mean(iris$Petal.Length)
)

# 5) evaluate overall area under
# the curve
cat(
  "Micro-averaged area under the ROC curve", roc.auc(
    actual    = actual,
    response  = response,
    micro     = TRUE
  ),
  "Micro-averaged area under the ROC curve (weighted)", weighted.roc.auc(
    actual    = actual,
    response  = response,
    w         = iris$Petal.Length/mean(iris$Petal.Length),
    micro     = TRUE
  ),
  sep = "\n"
)