# objective: Test that Fowlks Mallows Index
# implemented in {SLmetrics} is aligned with
# target functions.

testthat::test_that(
  desc = "Test `fmi()`-function", code = {

    testthat::skip_on_cran()

    # 0) construct fmi
    # wrapper
    wrapped_fmi <- function(
      actual,
      predicted,
      w = NULL) {
      
        if (is.null(w)) {
          fmi(
            actual     = actual,
            predicted  = predicted
          )
        } else {
          weighted.fmi(
            actual     = actual,
            predicted  = predicted,
            w = w
          )
        }
      
        
      
    }

    wrapped_ref_fmi <- function(
      actual,
      predicted,
      w = NULL
    ) {
      if (is.null(w)) {
        py_fmi(
          actual   = actual,
          predicted = predicted
        )
      } else {
        ref_fmi(
          actual    = actual,
          predicted = predicted,
          w         = w
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
        # 2.1) generate sensible 
        # label information
        info <- paste(
          "Balanced = ", balanced
        )

        # 2.2) generate score
        # from {slmetrics}
        score <- wrapped_fmi(
          actual     = actual,
          predicted  = predicted,
          w          = if (weighted) w else NULL
        )

        # 2.3) test that the values
        # are sensible the values 
        # can be NA
        testthat::expect_true(is.numeric(score), info = info)
        testthat::expect_true(length(score) == 1, info = info)

        # 2.4) test that the values
        # are equal to target value

        # 2.4.1) calculate py_score
        py_score <- wrapped_ref_fmi(
          actual    = actual,
          predicted = predicted,
          w         = if (weighted) w else NULL
        )

        # 2.4.2) test for equality
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