# 1) recode Iris
# to binary classification
# problem
iris$species_num <- as.numeric(
  iris$Species == "virginica"
)

# 1.1) set some arbitrary
# weight
iris$weights <- rbeta(
  n = nrow(iris),
  shape1 = 20,
  shape2 = 1
)

# 2) fit the logistic
# regression
model <- glm(
  formula = species_num ~ Sepal.Length + Sepal.Width,
  data    = iris,
  family  = binomial(
    link = "logit"
  ),
  weights = iris$weights
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

# 4) confusion matrix
confusion_matrix <- cmatrix(
  actual    = actual,
  predicted = predicted,
  w         = iris$weights
)

# 4.1) summarise matrix
summary(
  confusion_matrix
)

# 4.2) plot confusion
# matrix
plot(
  confusion_matrix
)