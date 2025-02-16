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
      for (weighted in c(TRUE, FALSE)) {
        for (center in c(TRUE, FALSE)) {
          for (method in c("unbiased", "ML")) {


            # 1) expected value
            if (weighted) {
              expected_value <- stats::cov.wt(
                cbind(
                  actual,
                  predicted
                ),
                wt = w,
                cor = cor,
                center = center,
                method = method
              )
            } else {
              expected_value <- stats::cov.wt(
                cbind(
                  actual,
                  predicted
                ),
                cor = cor,
                center = center,
                method = method
              )
            }


            # 2) set equal with
            # cov.wt
            testthat::expect_equal(
              object = SLmetrics:::cov.wt(
                cbind(
                  actual,
                  predicted
                ),
                wt  = if (weighted) w else NULL,
                cor = cor,
                center = center,
                method = method
              ),
              expected = expected_value
            )


          }
        }
      }
    }
    

    
  }
)