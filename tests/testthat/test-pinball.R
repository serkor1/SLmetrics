# script: Test Pinball
# date: 2024-10-18
# author: Serkan Korkmaz, serkor1@duck.com
# objective:
#
# Test that pinball deviance
# is correctly implemmented
#
# script start;

testthat::test_that(
  desc = "Test that `pinball(deviance = TRUE)` is correctly implemented",
  code = {

    # 0) load functions from
    # {scikit-learn} and {pytorch}
    reticulate::source_python(
      "scikit-learn.py"
    )

    reticulate::source_python(
      "pytorch.py"
    )


    # 1) generate actual
    # and predicted values
    values <- create_regression()
    actual <- values$actual
    predicted <- values$predicted
    w <- values$weight

    testthat::expect_true(
      all(
        set_equal(
          current = pinball(actual, predicted, deviance = TRUE),
          target  = py_d2pinball(actual, predicted)
        ),
        set_equal(
          current   = pinball(actual, predicted, w = w, deviance = TRUE),
          target    = py_d2pinball(actual, predicted, w = w),
          tolerance = 1e-4
        )
      )
    )

  }
)

# script end;
