# objective: Test that the metric
# implemented in {SLmetrics} is aligned with
# target functions.

testthat::test_that(
  desc = "Test `fdr()`-function", code = {

    testthat::skip_on_cran()

    # 0) construct Balanced Accuracy
    # wrapper
    wrapped_fdr <- function(
      actual,
      predicted,
      w = NULL,
      estimator = 0) {
      
        if (is.null(w)) {
          fdr(
            actual     = actual,
            predicted  = predicted,
            estimator  = estimator
          )
        } else {
          weighted.fdr(
            actual     = actual,
            predicted  = predicted,
            w          = w,
            estimator  = estimator
          )
        }
      
    }
    
    for (balanced in c(FALSE, TRUE)) {

      # 1) generate class
      # values
      actual    <- create_factor(balanced = balanced)
      predicted <- create_factor(balanced = balanced)
      w         <- runif(n = length(actual))

      for (weighted in c(TRUE, FALSE)) {
      
        # 2) test that the are 
        # equal to target values
        for (estimator in c(0:2)) {

          # 2.1) generate sensible 
          # label information
          info <- paste(
            "Balanced = ", balanced,
            "Weighted = ", weighted,
            "estimator = ", estimator
          )

          # 2.2) generate score
          # from {slmetrics}
          score <- wrapped_fdr(
            actual     = actual,
            predicted  = predicted,
            w          = if (weighted) w else NULL,
            estimator  = estimator
          )

          # 2.3) test that the values
          # are sensible the values 
          # can be NA
          testthat::expect_true(is.numeric(score), info = info)

          # 2.4) test that the values
          # are equal to target value

          # 2.4.1) calculate ref_score
          ref_score <- ref_fdr(
            actual    = actual,
            predicted = predicted,
            estimator = estimator,
            w         = if (weighted) w else NULL
          )

          # 2.4.2) test for equality
          testthat::expect_true(
            object = set_equal(
              current = as.numeric(score),
              target  = as.numeric(ref_score)
            ),
            info = info
          )

        }

      }

    }
  }
)