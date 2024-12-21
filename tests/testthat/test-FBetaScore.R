# objective: Test that FBetaScorre
# implemented in {SLmetrics} is aligned with
# target functions.

testthat::test_that(
  desc = "Test `fbeta()`-function", code = {

    # 0) construct Balanced Accuracy
    # wrapper
    wrapped_fbeta <- function(
      actual,
      predicted,
      beta,
      w = NULL,
      micro = TRUE) {
      
        if (is.null(w)) {
          fbeta(
            actual     = actual,
            predicted  = predicted,
            beta       = beta,
            micro      = micro
          )
        } else {
          weighted.fbeta(
            actual     = actual,
            predicted  = predicted,
            w          = w,
            beta       = beta,
            micro      = micro
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
        for (beta in c(0, 4, 8)) {
          for (micro in c(NA, TRUE, FALSE)) {

             
          # 2.1) generate sensible 
          # label information
          info <- paste(
            "Balanced = ", balanced,
            "beta = ", beta,
            "Weighted = ", weighted,
            "Micro =", micro
          )

          # 2.2) generate score
          # from {slmetrics}
          score <- wrapped_fbeta(
            actual     = actual,
            predicted  = predicted,
            beta       = beta,
            w          = if (weighted) w else NULL,
            micro      = if (is.na(micro)) { NULL } else micro
          )

          # 2.3) test that the values
          # are sensible the values 
          # can be NA
          testthat::expect_true(is.numeric(score), info = info)

          # 2.4) test that the values
          # are equal to target value

          # 2.4.1) calculate py_score
          py_score <- py_fbeta(
            actual    = actual,
            predicted = predicted,
            beta      = beta,
            average   = if (is.na(micro)) { NULL } else ifelse(micro, "micro", "macro"),
            w         = if (weighted) w else NULL
          )
            
          py_score[is.na(py_score)] <- score[is.na(score)] <- 0.0
            
          # 2.4.2) test for equality
          testthat::expect_true(
            object = set_equal(
              current = score,
              target  = py_score
            ),
            info = info
          )

          }
        }

      }

    }
  }
)