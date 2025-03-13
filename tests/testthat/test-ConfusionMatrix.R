# objective: Test that Confusion Matrix
# implemented in {SLmetrics} is aligned with
# target functions.

testthat::test_that(
  desc = "Test `cmatrix()`-function", code = {

    testthat::skip_on_cran()

    # 2) test that the are 
    # equal to target values
    for (OpenMP in c(TRUE, FALSE)) {

      # 2.1) enable/disable
      # OpenMP
      if (OpenMP) {
        openmp.on()
      } else {
        openmp.off()
      }

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
            "Weighted = ", weighted,
            "OpenMP   = ", OpenMP 
          )
  
          # 2.3) generate confusion
          # matrix
          if (weighted) {
  
            confusion_matrix <- weighted.cmatrix(
              actual    = actual,
              predicted = predicted,
              w         = w
            )
            
          } else {
  
            confusion_matrix <- cmatrix(
              actual    = actual,
              predicted = predicted
            )
  
          }
          
  
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
              current = as.numeric(confusion_matrix),
              target  = as.numeric(py_confusion_matrix)
            ),
            info = info
          )
  
          # 2.6) test that
          # methods works
  
          # 2.6.1) print method
          testthat::expect_no_condition(
            object = invisible(SLmetrics:::print.cmatrix(confusion_matrix))
          )
  
          # 2.6.2) summary method
          testthat::expect_no_condition(
            object = invisible(SLmetrics:::summary.cmatrix(confusion_matrix))
          )
  
          # 2.6.3) plot method
          testthat::expect_no_condition(
            object = invisible(SLmetrics:::plot.cmatrix(confusion_matrix))
          )
  
  
  
        }
    
      }

    }

  }
)

