# script: Test R Squared
# date: 2024-10-10
# author: Serkan Korkmaz, serkor1@duck.com
# objective: This is tested directly
# against LM
# script start;

testthat::test_that(
  desc = "Test that `rsq()`-function is consistent with the `lm()`-function",
  code = {

    # 0) run a regression
    # on mtcars
    model <-  lm(
      formula = mpg ~ .,
      data    = mtcars
    )

    # 1) extract rsq
    target_rsq    <- summary(model)$r.squared
    target_adjrsq <- summary(model)$adj.r.squared

    # 2) calculate rsq
    # manually
    sl_rsq <- rsq(
      actual = mtcars$mpg,
      predicted = fitted.values(model)
    )

    sl_adjrsq <- rsq(
      actual = mtcars$mpg,
      predicted = fitted.values(model),
      k = ncol(model.matrix(model)) - 1
    )

    # 3) testtat they are
    # all exactly equal
    testthat::expect_true(
      set_equal(
        target  = c(target_rsq, target_adjrsq),
        current = c(sl_rsq, sl_adjrsq)
      )
    )

    # 4) testthat missing
    # values are handled correctly

    # 4.1) create actual and predicted
    # with large noise
    actual    <- rnorm(n = 100)
    predicted <- actual + rnorm(n = 100, 10, 10)

    # 4.2) test that they are equal
    testthat::expect_true(
      set_equal(
        target  = rsq(actual, predicted), 
        current = rsq(c(actual, NA), c(predicted, NA),na.rm = TRUE)
      )
    )
  }
)

# script end;
