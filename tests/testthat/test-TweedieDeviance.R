# objective: Test that the metric
# implemented in {SLmetrics} is aligned with
# target functions.

testthat::test_that(
  desc = "Test `tweedie.deviance()`-function", code = {

    testthat::skip_on_cran()

    # 0) construct tweedie-wrapper
    wrapped_tweedie_deviance <- function(
      actual,
      predicted,
      w = NULL,
      power = 2) {
        if (is.null(w)) {
          deviance.tweedie(
            actual = actual,
            predicted = predicted,
            power = power
          )
        } else {
          weighted.deviance.tweedie(
            actual = actual,
            predicted = predicted,
            w = w,
            power = power
          )
        }
    }

    for (weighted in c(FALSE, TRUE)) {

      for (power in c(-2L:2L)) {

        # 0) create regression
        # for the test
        values    <- create_regression()
        actual    <- values$actual
        predicted <- values$predicted
        w         <- if (weighted) values$weight else NULL

        # 1) generate sensible
        # label information
        info <- paste(
          "Weighted = ", weighted,
          "Power =", power
        )

        # 2) generate score
        # from {slmetrics}
        score <- wrapped_tweedie_deviance(
          actual     = actual,
          predicted  = predicted,
          w          = w,
          power      = power
        )

        # 2.1) test that the values
        # are sensible
        testthat::expect_true(is.numeric(score), info = info)
        testthat::expect_true(!is.na(score), info = info)
        testthat::expect_true(length(score) == 1, info = info)

        # 2.2) calculate reference value
        py_score <- py_tweedie(
          actual     = actual,
          predicted  = predicted,
          w          = w,
          power      = power
        )

        # 2.3) test for equality
        testthat::expect_true(
          object = set_equal(
            current = as.numeric(score),
            target  = as.numeric(py_score)
          ),
          info = info
        )

        }

      

    } 
  }
)