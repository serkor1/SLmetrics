# objective: Test that the brier score metric
# implemented in {SLmetrics} is aligned with
# expected behavior.
testthat::test_that(
  desc = "Test `brier()`-function", code = {
    testthat::skip_on_cran()
    
    # 0) construct brier-wrapper
    wrapped_brier <- function(
      p,
      q,
      w = NULL) {
      if (is.null(w)) {
        brier(
          p = p,
          q = q
        )
      } else {
        weighted.brier(
          p = p,
          q = q,
          w = w
        )
      }
    }
    
    for (weighted in c(FALSE, TRUE)) {
      # 0) create classification
      # for the test
      p <- runif(n = 100)
      q <- runif(n = 100)
      weight <- runif(n = 100)
      w <- if (weighted) weight else NULL
      
      # 1) generate sensible
      # label information
      info <- paste(
        "Weighted = ", weighted
      )
      
      # 2) generate score
      # from {slmetrics}
      score <- wrapped_brier(
        p = p,
        q = q,
        w = w
      )
      
      # 2.1) test that the values
      # are sensible
      testthat::expect_true(is.numeric(score), info = info)
      testthat::expect_true(!is.na(score), info = info)
      testthat::expect_true(length(score) == 1, info = info)
      
      # 2.2) Manual calculation of brier score for validation
      if (is.null(w)) {
        # Unweighted brier score
        expected_score <- mean((q - p)^2)
      } else {
        # Weighted brier score
        expected_score <- sum(w * (q - p)^2) / sum(w)
      }
      
      # 2.3) test for equality
      testthat::expect_equal(
        object = as.numeric(score),
        expected = as.numeric(expected_score),
        info = info
      )
    }
  }
)