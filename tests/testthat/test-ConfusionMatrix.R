# objective: Test that Confusion Matrix
# implemented in {SLmetrics} is aligned with
# target functions.

testthat::test_that(
  desc = "Test `cmatrix()`-function", code = {

    # 2) test that the are 
    # equal to target values
    for (balanced in c(TRUE, FALSE)) {

      # 2.1) generate class
      # values and weights
      actual    <- create_factor(balanced = balanced)
      predicted <- create_factor(balanced = balanced)
      w         <- runif(n = length(actual))

      for (weighted in c(TRUE, FALSE)) {

        # 2.2) generate sensible 
        # label information
        info <- paste(
          "Balanced = ", balanced,
          "Weighted = ", weighted
        )

        # 2.3) generate confusion
        # matrix
        confusion_matrix <- cmatrix(
          actual    = actual,
          predicted = predicted,
          w         = if (weighted) w else NULL 
        )

        # 2.3) test that the values
        # are sensible
        testthat::expect_true(dim(confusion_matrix)[1] == dim(confusion_matrix)[2], info = info)
        testthat::expect_true(dim(confusion_matrix)[1] == length(levels(actual)), info = info)

        # 2.4) test that the values
        # are equal to target
        py_confusion_matrix <- py_cmatrix(
          actual    = actual,
          predicted = predicted,
          w         = if (weighted) w else NULL 
        )

        # 2.5) test for equality
        testthat::expect_true(
          object = set_equal(
            current = confusion_matrix,
            target  = py_confusion_matrix
          ),
          info = info
        )



      }
  
    }
  }
)

