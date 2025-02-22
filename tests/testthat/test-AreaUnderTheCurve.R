# objective: Test that Accuracy
# implemented in {SLmetrics} is aligned with
# target functions.

testthat::test_that(
  desc = "Test `auc()`-function", code = {

    # 0) skip on CRAN
    testthat::skip_on_cran()

    for (ordered in c(TRUE, FALSE)) {

      # 1) generate x and y
      # pair
      if (ordered) {
        x <- seq(0, pi, length.out = 200)
      } else {
        x <- sample(seq(0, pi, length.out = 200))
      }
    
      y <- sin(x)

      # 2) calculate AUC
      # based on methods
      for (method in c(0, 1)) {

        # 2.1) calculate value
        score <- auc(
          y = y,
          x = x, 
          method = method, 
          ordered = ordered
        )

        # 2.2) check that that the
        # value is numeric and of length
        # one
        testthat::expect_true(is.numeric(score))
        testthat::expect_true(length(score) == 1)
      
      }
    }
  }
)