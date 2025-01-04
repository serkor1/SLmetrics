# 1) Recode the iris data set to a binary classification problem
#    Here, the positive class ("Virginica") is coded as 1,
#    and the rest ("Others") is coded as 0.
iris$species_num <- as.numeric(iris$Species == "virginica")

# 2) Fit a logistic regression model predicting species_num from Sepal.Length & Sepal.Width
model <- glm(
  formula = species_num ~ Sepal.Length + Sepal.Width,
  data    = iris,
  family  = binomial(link = "logit")
)

# 3) Generate predicted classes: "Virginica" vs. "Others"
predicted <- factor(
  as.numeric(predict(model, type = "response") > 0.5),
  levels = c(1, 0),
  labels = c("Virginica", "Others")
)

# 3.1) Generate actual classes
actual <- factor(
  x      = iris$species_num,
  levels = c(1, 0),
  labels = c("Virginica", "Others")
)

# For Log Loss, we need predicted probabilities for each class.
# Since it's a binary model, we create a 2-column matrix:
#   1st column = P("Virginica")
#   2nd column = P("Others") = 1 - P("Virginica")
predicted_probs <- predict(model, type = "response")
response_matrix <- cbind(predicted_probs, 1 - predicted_probs)

# 4) Evaluate unweighted Log Loss
#    'logloss' takes (actual, response_matrix, normalize=TRUE/FALSE).
#    The factor 'actual' must have the positive class (Virginica) as its first level.
unweighted_LogLoss <- logloss(
  actual    = actual,           # factor
  response  = response_matrix,  # numeric matrix of probabilities
  normalize = TRUE              # normalize = TRUE
)

# 5) Evaluate weighted Log Loss
#    We introduce a weight vector, for example:
weights <- iris$Petal.Length / mean(iris$Petal.Length)
weighted_LogLoss <- weighted.logloss(
  actual    = actual,
  response  = response_matrix,
  w         = weights,
  normalize = TRUE
)

# 6) Print Results
cat(
  "Unweighted Log Loss:", unweighted_LogLoss,
  "Weighted Log Loss:", weighted_LogLoss,
  sep = "\n"
)
