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

    # 2) test for unweighted deviance
    # equality
    testthat::expect_true(
      object = set_equal(
        current = as.numeric(pinball(actual, predicted, deviance = TRUE)),
        target  = as.numeric(py_d2pinball(actual, predicted))
      ),
      label = "(unweighted) Pinball deviance is not equal to {scikit-learn} implementation"
    )

    # 3) test for weighted deviance
    # equality
    testthat::expect_true(
      object = set_equal(
        current = as.numeric(weighted.pinball(actual, predicted, w = w, deviance = TRUE)),
        target  = as.numeric(py_d2pinball(actual, predicted, w = w))
      ),
      label = "(weightted) Pinball deviance is not equal to {scikit-learn} implementation"
    )

  }
)

# script end;
