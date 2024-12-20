# 1) fit a linear
# regression
model <- lm(
  mpg ~ .,
  data = mtcars
)

# 1.1) define actual
# and predicted values
# to measure performance
actual    <- mtcars$mpg
predicted <- fitted(model)

# 2) evaluate in-sample model
# performance
cat(
  "Concordance Correlation Coefficient", ccc(
    actual     = actual,
    predicted  = predicted,
    correction = FALSE
  ),
  "Concordance Correlation Coefficient (corrected)", ccc(
    actual     = actual,
    predicted  = predicted,
    correction = TRUE
  ),
  "Concordance Correlation Coefficient (weigthed)", weighted.ccc(
    actual     = actual,
    predicted  = predicted,
    w          = mtcars$mpg/mean(mtcars$mpg),
    correction = FALSE
  ),
  sep = "\n"
)
