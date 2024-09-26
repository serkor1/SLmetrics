# script: RSQ Tests
# author: Serkan Korkmaz, serkor1@duck.com
# date: 2024-08-26
# objective: Test that rsq returns a non-zero
# positive value for all values passed into it
# script start;

testthat::test_that(
  desc = "`rsq`-function returns non-zero postive values",
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
      all.equal(
        target = c(target_rsq, target_adjrsq),
        current = c(sl_rsq, sl_adjrsq)
      )
    )

  }
)

# script end;
