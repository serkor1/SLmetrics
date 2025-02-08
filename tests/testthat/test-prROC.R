# script: Precision Recall Curve
# date: 2024-12-28
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Test that it returns
# whatever it should return - and correctly.
# script start;

testthat::test_that(
  desc = "Test that `prROC()`-function works as expected", code = {

    testthat::skip_on_cran()

    # 0) construct ROC
    # wrapper
    wrapped_prROC <- function(
      actual,
      response,
      thresholds = NULL,
      w = NULL,
      micro = TRUE) {
      
      if (is.null(w)) {

        prROC(
          actual,
          response,
          thresholds = if (is.null(thresholds))  {NULL} else thresholds
        )

      } else {

        weighted.prROC(
          actual,
          response,
          thresholds = if (is.null(thresholds))  {NULL} else thresholds,
          w = w
        )

      }
      
      
    }

    # 1) generate class
    # values
    actual     <- create_factor(n = 100, k = 5)
    response   <- runif(n = length(actual))
    w          <- runif(n = length(actual))
    thresholds <- seq(0.1, 0.9, by = 0.1)

    for (weighted in c(TRUE, FALSE)) {
    
      # 2) test that the are 
      # equal to target values
      for (micro in c(NA, TRUE, FALSE)) {

        # 2.1) generate sensible 
        # label information
        info <- paste(
          "Weighted = ", weighted,
          "Micro = ", micro
        )

        # 2.2) generate score
        # from {slmetrics}
        score <- wrapped_prROC(
          actual     = actual,
          response   = response,
          w          = if (weighted) w else NULL,
          micro      = if (is.na(micro)) { NULL } else micro
        )

        # 2.3) Test that methods
        # works as expected
        testthat::expect_no_condition(
          object = invisible(capture.output(print(score))),
          message = info
        )

        testthat::expect_no_condition(
          object = invisible(capture.output(summary(score))),
          message = info
        )

        testthat::expect_no_condition(
          object  = plot(score, panels = FALSE),
          message = info
        )

        testthat::expect_no_condition(
          object  = plot(score, panels = TRUE),
          message = info
        )
        

        # 2.4) test that the values
        # are equal to target value

        # 2.4.1) calculate py_score
        py_score <- do.call(
          rbind,
          lapply(py_prROC(
            actual    = actual,
            response  = response,
            w         = if (weighted) w else NULL),
            FUN = as.data.frame)
          )

        # 2.4.2) test for equality
        testthat::expect_true(
          object = set_equal(
            current = score[is.finite(score$thresholds),],
            target  = py_score[is.finite(py_score$thresholds),]
          ),
          info = info
        )


      }

    }


  }
)
