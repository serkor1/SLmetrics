# objective: Test that the brier score metric
# implemented in {SLmetrics} is aligned with
# expected behavior.
testthat::test_that(
  desc = "Test `brier()`-function", code = {
    testthat::skip_on_cran()
    
    # 0) construct brier-wrapper
    wrapped_brier <- function(
      ok,
      qk,
      w = NULL) {
      if (is.null(w)) {
        brier.score(
          ok = ok,
          qk = qk
        )
      } else {
        weighted.brier.score(
          ok = ok,
          qk = qk,
          w = w
        )
      }
    }
    
    n_obs <- 10;
    n_classes <- 3
    for (weighted in c(FALSE, TRUE)) {
      # 0) create classification
      # for the test
      ok <- diag(n_classes)[ sample.int(n_classes, n_obs, TRUE), ]
      qk <- matrix(rep(1/n_classes,n_obs * n_classes), n_obs, n_classes)
      qk <- qk / rowSums(qk)
      weight <- rep(1, n_obs)
      w <- if (weighted) weight else NULL
      
      # 1) generate sensible
      # label information
      info <- paste(
        "Weighted = ", weighted
      )
      
      # 2) generate score
      # from {slmetrics}
      score <- wrapped_brier(
        ok = ok,
        qk = qk,
        w  = w
      )
      
      # 2.1) test that the values
      # are sensible
      testthat::expect_true(is.numeric(score), info = info)
      testthat::expect_true(!is.na(score), info = info)
      testthat::expect_true(length(score) == 1, info = info)
      
      # 2.2) Manual calculation of brier score for validation
      expected_score <- py_brier(
        as.numeric(ok),
        as.numeric(qk),
        w = if (weighted) rep(w, n_classes) else NULL
      )
      
      # 2.3) test for equality
      testthat::expect_true(
        object = set_equal(
          target  = as.numeric(expected_score),
          current = as.numeric(score)
        ),
        info = info
      )
    }
  }
)