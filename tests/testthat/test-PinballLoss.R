# objective: Test that PinballLoss
# implemented in {SLmetrics} is aligned with
# target functions.
testthat::test_that(
  desc = "Test `pinball()`-function", code = {

    testthat::skip_on_cran()

    # 0) construct Balanced Accuracy
    # wrapper
    wrapped_pinball <- function(
      actual,
      predicted,
      alpha,
      deviance,
      w = NULL) {
        if (is.null(w)) {
          pinball(
            actual     = actual,
            predicted  = predicted,
            deviance   = deviance,
            alpha      = alpha
          )
        } else {
          weighted.pinball(
            actual     = actual,
            predicted  = predicted,
            alpha      = alpha,
            deviance   = deviance,
            w          = w
          )
        }
      }
    
    wrapped_pypinball <- function(
      actual,
      predicted,
      alpha,
      deviance,
      w = NULL
    ) {

      if (deviance) {
        py_d2pinball(
          actual = actual,
          predicted = predicted,
          w = w,
          alpha = alpha
        )
      } else {
        py_pinball(
          actual = actual,
          predicted = predicted,
          w = w,
          alpha = alpha
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
        for (deviance in c(TRUE, FALSE)) {

          # 2) test that the are 
          # equal to target values
          for (alpha in c(0.2, 0.5, 0.8)) {
            
            # 2.1) generate sensible 
            # label information
            info <- paste(
              "Alpha = ", alpha,
              "Deviance = ", deviance,
              "Weighted = ", weighted
            )

            # 2.2) generate score
            # from {slmetrics}
            score <- wrapped_pinball(
              actual     = actual,
              predicted  = predicted,
              alpha      = alpha,
              deviance   = deviance,
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
            py_score <- wrapped_pypinball(
              actual     = actual,
              predicted  = predicted,
              deviance   = deviance,
              alpha      = alpha,
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
