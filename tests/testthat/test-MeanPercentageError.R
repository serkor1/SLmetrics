# objective: Test that the metric
# implemented in {SLmetrics} is aligned with
# target functions.

testthat::test_that(
  desc = "Test `mpe()`-function", code = {

    testthat::skip_on_cran()

    # 0) construct mpe-wrapperr
    wrapped_mpe <- function(
      actual,
      predicted,
      w = NULL) {
        if (is.null(w)) {
          mpe(
            actual = actual,
            predicted = predicted
          )
        } else {
          weighted.mpe(
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
      w         <- if (weighted) values$weight else NULL

      # 1) generate sensible
      # label information
      info <- paste(
        "Weighted = ", weighted
      )

      # 2) generate score
      # from {slmetrics}
      score <- wrapped_mpe(
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
      py_score <- py_mpe(
        actual     = actual,
        predicted  = predicted,
        w          = w
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
)