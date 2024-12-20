# script: Regression Tests
# date: 2024-12-18
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Test that weighted regression methods
# are consistent with equivalent python methods
# and retrurns sensible values
# script start;

testthat::test_that(
  desc = "Test that all weighted regression metrics are correctly implemented",
  code = {

    # 1) generate actual
    # and predicted values
    values <- create_regression()
    actual <- values$actual
    predicted <- values$predicted
    w <- values$weight

    # 2) generate functions
    # lists
    sl_function <- list(
      "rmse"      = weighted.rmse,
      "rmsle"     = weighted.rmsle,
      "rrmse"     = weighted.rrmse,
      "rae"       = weighted.rae,
      "mape"      = weighted.mape,
      "smape"     = weighted.smape,
      "mpe"       = weighted.mpe,
      "mse"       = weighted.mse,
      "ccc"       = weighted.ccc,
      "huberloss" = weighted.huberloss,
      "mae"       = weighted.mae,
      "pinball"   = weighted.pinball
    )

    # 3) test that the functions
    # returns the same values as
    # their python equivalents
    py_function <- Filter(
      Negate(is.null),

      setNames(
        lapply(seq_along(sl_function), function(i) {
          tryCatch(
            get(paste0("py_",names(sl_function)[i])),
            error = function(e) {
              NULL
            }
          )

        }),
        paste0("py_", names(sl_function))
      )
    )

    sl_function <- sl_function[
      names(sl_function) %in% gsub("py_", "", names(py_function))
    ]


    for (i in seq_along(sl_function)) {

      .f <-  sl_function[[i]]
      .F <-  py_function[[i]]

      # 1) replace missing with 0
      # as in python
      sl_measure <- .f(actual, predicted, w = w);

      py_measure <- as.numeric(reticulate::py_suppress_warnings(.F(actual, predicted, w = w)))

      testthat::expect_true(
        object = set_equal(
          sl_measure,
          py_measure

        ),
        label = paste(
          "Weighted functions in",
          names(sl_function)[i],
          "not equivalent to {torch} or {scikit-learn}."
        )
      )

    }

  }
)

# script end;
