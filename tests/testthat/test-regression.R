# script: Regression Tests
# date: 2024-10-07
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Test that regression methods
# are consistent with equivalent python methods
# and retrurns sensible values
# script start;

testthat::test_that(
  desc = "Test that all regression metrics are correctly implemented",
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

    # 2) generate functions
    # lists
    sl_function <- list(
      # RMSE
      "RMSE" = rmse
    )


  }
)

# script end;
