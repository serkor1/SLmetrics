# script: Test Binary Classification entropy
# author: Serkan Korkmaz, serkor1@duck.com
# date: 2024-08-26
# objective: Test that the binary classification
# entropy returns a proper value
# script start;

testthat::test_that(
  desc = "`entropy`-function returns non-zero postive values",
  code = {

    # 0) generate values
    # from a normal distribution
    actual <-  rbinom(
      n    = 1e2,
      size = 1,
      prob =  0.5
    )

    predicted <- runif(
      n    = 1e2,
      min = .1,
      max = .9
    )


    # 1) calculate the
    # rsq using rsq()-function
    output <- testthat::expect_no_condition(
      entropy(
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
