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
      "rmse"      = rmse,
      "mse"       = mse,
      "rmsle"     = rmsle,
      "huberloss" = huberloss,
      "mpe"       = mpe,
      "mape"      = mape,
      "smape"     = smape,
      "rae"       = rae,
      "rrmse"     = rrmse,
      "mae"       = mae,
      "ccc"       = ccc
    )

    # 3) test that the functions
    # runs without errors
    for (i in seq_along(sl_function)) {

      .f <-  sl_function[[i]]

      testthat::expect_true(
        all(
          is.numeric(.f(actual, predicted, w = w)),
          is.numeric(.f(actual, predicted)),
          length(.f(actual, predicted, w = w)) == 1,
          length(.f(actual, predicted)) == 1
        )
      )

    }

    # 4) test that the functions
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
      sl_measure <- .f(actual, predicted);

      py_measure <- as.numeric(reticulate::py_suppress_warnings(.F(actual, predicted)))

      testthat::expect_true(
        object = set_equal(
          sl_measure,
          py_measure,
          tolerance = 1e-5

        ),
        label = paste(
          "Unweighted functions in",
          names(sl_function)[i],
          "not equivalent to {torch} or {scikit-learn}."
        )
      )

    }

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
          py_measure,
          tolerance = 1e-5

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
