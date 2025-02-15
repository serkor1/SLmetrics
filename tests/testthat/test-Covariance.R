# objective: Test that the function
# implemented in {SLmetrics} is aligned with
# target functions.

testthat::test_that(
  desc = "Test the internal `cov.wt()`-function", code = {

    testthat::skip_on_cran()

    # 1) generate regression
    # values
    values <- create_regression()
    actual <- values$actual
    predicted <- values$predicted
    w         <- values$weight

    for (cor in c(TRUE, FALSE)) {
      # 2) set equal with
      # cov.wt
      testthat::expect_equal(
        object = SLmetrics:::cov.wt(
          cbind(
            actual,
            predicted
          ),
          cor = cor
        ),
        expected = stats::cov.wt(
          cbind(
            actual,
            predicted
          ),
          cor = cor
        )
      )
    }
    

    
  }
)