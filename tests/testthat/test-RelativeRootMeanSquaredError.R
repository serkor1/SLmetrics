# objective: Test that the metric
# implemented in {SLmetrics} is aligned with
# target functions.

testthat::test_that(
  desc = "Test `rrmse()`-function", code = {

    # 0) construct rrmse-wrapperr
    wrapped_rrmse <- function(
      actual,
      predicted,
      w = NULL) {
        if (is.null(w)) {
          rrmse(
            actual = actual,
            predicted = predicted
          )
        } else {
          weighted.rrmse(
            actual = actual,
            predicted = predicted,
            w = w
          )
        }
    }

    for (weighted in c(FALSE, TRUE)) {

      # 0) create regression
      # for the test
      values    <- create_regression()
      actual    <- values$actual
      predicted <- values$predicted
      w         <- if (weighted) NULL else values$weights

      # 1) generate sensible
      # label information
      info <- paste(
        "Weighted = ", weighted
      )

      # 2) generate score
      # from {slmetrics}
      score <- wrapped_rrmse(
        actual     = actual,
        predicted  = predicted,
        w          = w
      )

      # 2.1) test that the values
      # are sensible
      testthat::expect_true(is.numeric(score), info = info)
      testthat::expect_true(!is.na(score), info = info)
      testthat::expect_true(length(score) == 1, info = info)

      # 2.2) calculate reference value
      py_score <- py_rrmse(
        actual     = actual,
        predicted  = predicted,
        w          = w
      )

      # 2.3) test for equality
      testthat::expect_true(
        object = set_equal(
          current = score,
          target  = py_score
        ),
        info = info
      )

    } 
  }
)