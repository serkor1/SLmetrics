# objective: Test that CohensKappa
# implemented in {SLmetrics} is aligned with
# target functions.
testthat::test_that(
  desc = "Test `ckappa()`-function", code = {

    testthat::skip_on_cran()

    # 0) construct Balanced Accuracy
    # wrapper
    wrapped_ckappa <- function(
      actual,
      predicted,
      beta = 0,
      w = NULL) {
        if (is.null(w)) {
          ckappa(
            actual     = actual,
            predicted  = predicted,
            beta       = beta
          )
        } else {
          weighted.ckappa(
            actual     = actual,
            predicted  = predicted,
            beta       = beta,
            w          = w
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
        for (beta in c(0, 1, 2)) {
          
          # 2.1) generate sensible 
          # label information
          info <- paste(
            "Balanced = ", balanced,
            "Beta = ", beta,
            "Weighted = ", weighted
          )

          # 2.2) generate score
          # from {slmetrics}
          score <- wrapped_ckappa(
            actual     = actual,
            predicted  = predicted,
            beta       = beta,
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
          py_score <- py_ckappa(
            actual     = actual,
            predicted  = predicted,
            penalty    = switch(as.character(beta),
            "0" = NULL,
            "1" = "linear",
            "2" = "quadratic"),
            w          = if (weighted) w else NULL
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
  }
)