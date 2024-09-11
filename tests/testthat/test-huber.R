# script: Huber Loss test
# author: Serkan Korkmaz, serkor1@duck.com
# date: 2024-08-26
# objective: Test that the huber loss function
# returns a non-zero value
# script start;


testthat::test_that(
  desc = "`huberloss`-function returns non-zero postive values",
  code = {

    # 0) generate values
    # from a normal distribution
    # and weights
    actual <- rnorm(
      n = 1e3
    )

    predicted <- actual + rnorm(
      n = 1e3
    )

    w <- rbeta(
      n = 1e3,
      shape1 = 10,
      shape2 = 2
    )


    # 1) calculate the metric
    # with and without weights
    # and assume that no errors
    # occurs.

    # 1.1) unweighted
    output <- testthat::expect_no_condition(
      huberloss(
        predicted,
        actual,
        delta = 5
      )
    )

    testthat::expect_true(
      output > 0
    )

    # 1.2) weighted
    # huber loss
    output <- testthat::expect_no_condition(
      whuberloss(
        predicted,
        actual,
        delta = 5,
        w = w
      )
    )

    testthat::expect_true(
      output > 0
    )



  }
)

# script end;
