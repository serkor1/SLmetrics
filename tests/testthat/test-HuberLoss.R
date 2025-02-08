# objective: Test that HuberLoss
# implemented in {SLmetrics} is aligned with
# target functions.
testthat::test_that(
  desc = "Test `huberloss()`-function", code = {

    testthat::skip_on_cran()

    # 0) construct Balanced Accuracy
    # wrapper
    wrapped_huberloss <- function(
      actual,
      predicted,
      delta,
      w = NULL) {
        if (is.null(w)) {
          huberloss(
            actual     = actual,
            predicted  = predicted,
            delta      = delta
          )
        } else {
          weighted.huberloss(
            actual     = actual,
            predicted  = predicted,
            delta      = delta,
            w          = w
          )
        }
      }
    
      # 1) generate regression
      # values
      values <- create_regression()
      actual <- values$actual
      predicted <- values$predicted
      w         <- values$weight

      for (weighted in c(TRUE, FALSE)) {
      
        # 2) test that the are 
        # equal to target values
        for (delta in c(1, 2, 3)) {
          
          # 2.1) generate sensible 
          # label information
          info <- paste(
            "delta = ", delta,
            "Weighted = ", weighted
          )

          # 2.2) generate score
          # from {slmetrics}
          score <- wrapped_huberloss(
            actual     = actual,
            predicted  = predicted,
            delta      = delta,
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
          py_score <- py_huberloss(
            actual     = actual,
            predicted  = predicted,
            delta      = delta,
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
)