# script: Accuracy
# author: Serkan Korkmaz, serkor1@duck.com
# date: 2024-08-26
# objective: Test wether the accuracy returns
# a non-zero value
# script start;

testthat::test_that(
  desc = "`accuracy`-function returns non-zero postive values",
  code = {

    # 0) generate values
    # from a normal distribution
    actual <-  rbinom(
      n    = 1e2,
      size = 1,
      prob =  0.5
    )

    predicted <- rbinom(
      n    = 1e2,
      size = 1,
      prob = 0.5
    )


    # 1) calculate the
    # rsq using rsq()-function
    output <- testthat::expect_no_condition(
      accuracy(
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
