# script: RSQ Tests
# author: Serkan Korkmaz, serkor1@duck.com
# date: 2024-08-26
# objective: Test that rsq returns a non-zero
# positive value for all values passed into it
# script start;

testthat::test_that(
  desc = "`rsq`-function returns non-zero postive values",
  code = {

    # 0) generate values
    # from a normal distribution
    actual <-  rnorm(
      n = 1e2
    )

    predicted <- actual + rnorm(
      n = 1e2
    )


    # 1) calculate the
    # rsq using rsq()-function
    output <- testthat::expect_no_condition(
      rsq(
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

# script end;
