# 0) run a regression
# on mtcars
model <- lm(
  formula = mpg ~ .,
  data    = mtcars
)

# 1) calculate
# rsq
rsq(
  actual    = mtcars$mpg,
  predicted = fitted.values(model)
)

# 1) calculate
# adjusted rsq
rsq(
  actual    = mtcars$mpg,
  predicted = fitted.values(model),
  k         = ncol(model.matrix(model)) - 1
)

