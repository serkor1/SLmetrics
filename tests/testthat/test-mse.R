# script: mse Tests
# author: Serkan Korkmaz, serkor1@duck.com
# date: 2024-08-24
# objective: Test that mse returns a non-zero
# positive value for all values passed into it
# script start;

testthat::test_that(
  desc = "`mse`-function returns non-zero postive values",
  code = {

    # 0) generate values
    # from a normal distribution
    actual <- rnorm(
      n = 1e2
    )

    predicted <- actual + rnorm(
      n = 1e2
    )

    # 1) calculate the
    # RMSE using mse()-function
    output <- testthat::expect_no_condition(
      mse(
        predicted,
        actual
      )
    )

    # 2) test that the value
    # is greater than 0
    testthat::expect_true(
      output > 0
    )

  }
)

testthat::test_that(
  desc = "`wmse`-function returns non-zero postive values",
  code = {

    # 0) generate values
    # from a normal distribution
    actual <- rnorm(
      n = 1e2
    )

    predicted <- actual + rnorm(
      n = 1e2
    )

    weights <- runif(
      n = 1e2
    )

    # 1) calculate the
    # RMSE using mse()-function
    output <- testthat::expect_no_condition(
      wmse(
        predicted,
        actual,
        weights
      )
    )

    # 2) test that the value
    # is greater than 0
    testthat::expect_true(
      output > 0
    )

  }
)

# script end;
