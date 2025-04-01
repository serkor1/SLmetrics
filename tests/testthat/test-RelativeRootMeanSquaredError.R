# objective: Test that the metric
# implemented in {SLmetrics} is aligned with
# target functions.

testthat::test_that(
  desc = "Test `rmse()`-function", code = {

    testthat::skip_on_cran()

    # 0) construct rmse-wrapperr
    wrapped_rrmse <- function(
      actual,
      predicted,
      w = NULL,
      normalization = 0) {
        if (is.null(w)) {
          rrmse(
            actual = actual,
            predicted = predicted,
            normalization = normalization
          )
        } else {
          weighted.rrmse(
            actual = actual,
            predicted = predicted,
            w = w,
            normalization = normalization
          )
        }
    }

    for (weighted in c(FALSE, TRUE)) {

      for (normalization in c(0, 1, 2, 3)) {

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
          "Normalization = ", normalization
        )

        # 2) generate score
        # from {slmetrics}
        score <- wrapped_rrmse(
          actual        = actual,
          predicted     = predicted,
          w             = w,
          normalization = normalization
        )

        # 2.1) test that the values
        # are sensible
        testthat::expect_true(is.numeric(score), info = info)
        testthat::expect_true(!is.na(score), info = info)
        testthat::expect_true(length(score) == 1, info = info)

        # 2.2) calculate reference value
        py_score <- ref_rrmse(
          actual        = actual,
          predicted     = predicted,
          w             = w,
          normalization = normalization
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