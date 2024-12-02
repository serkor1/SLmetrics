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



# 4) generate reciever
# operator characteristics
roc <- prROC(
  actual   = actual,
  response = response
)


# 5) plot by species
plot(roc)

# 5.1) summarise
summary(roc)

# 6) provide custom
# threholds
roc <- prROC(
  actual     = actual,
  response   = response,
  thresholds = seq(0, 1, length.out = 4)
)


# 5) plot by species
plot(roc)
