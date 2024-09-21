# script: Test `ccc()`-function
# author: Serkan Korkmaz, serkor1@duck.com
# date: 2024-09-20
# objective:
# script start;

testthat::test_that(
  desc = "`ccc()`-function returns double, without any conditions",
  code = {

    # 1) generate actual
    # and predicted values
    actual <- rnorm(n = 1e6)
    predicted <- actual + rnorm(n = 1e6)

    # 2) generate `ccc()` weighted
    # and unweigthed with and without
    # correction, expect the length 1
    # and is numeric
    for (correction in c(TRUE, FALSE)) {

      # 2.1) unweighted
      unweighted <- testthat::expect_no_condition(
        object = ccc(
          actual = actual,
          predicted = predicted,
          correction = correction
        )
      )

      testthat::expect_type(
        object = unweighted,
        type   = "double"
      )

      testthat::expect_length(
        object = unweighted,
        n      = 1
      )

      # 2.2) weighted
      weighted <- testthat::expect_no_condition(
        object = ccc(
          actual = actual,
          predicted = predicted,
          correction = correction
        )
      )

      testthat::expect_type(
        object = weighted,
        type   = "double"
      )

      testthat::expect_length(
        object = weighted,
        n      = 1
      )
    }

  }
)


testthat::test_that(
  desc = "`wccc()`-function returns double, without any conditions",
  code = {

    # 1) generate actual
    # and predicted values
    actual <- rnorm(n = 1e6)
    predicted <- actual + rnorm(n = 1e6)
    w <- runif(n = 1e6)

    # 2) generate `ccc()` weighted
    # and unweigthed with and without
    # correction, expect the length 1
    # and is numeric
    for (correction in c(TRUE, FALSE)) {

      # 2.1) unweighted
      unweighted <- testthat::expect_no_condition(
        object = wccc(
          actual     = actual,
          predicted  = predicted,
          w          = w,
          correction = correction
        )
      )

      testthat::expect_type(
        object = unweighted,
        type   = "double"
      )

      testthat::expect_length(
        object = unweighted,
        n      = 1
      )

      # 2.2) weighted
      weighted <- testthat::expect_no_condition(
        object = wccc(
          actual     = actual,
          predicted  = predicted,
          w          = w,
          correction = correction
        )
      )

      testthat::expect_type(
        object = weighted,
        type   = "double"
      )

      testthat::expect_length(
        object = weighted,
        n      = 1
      )
    }

  }
)

# script end;



