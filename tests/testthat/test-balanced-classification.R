# script: Classification Tests
# author: Serkan Korkmaz, serkor1@duck.com
# date: 2024-10-02
# objective: Test all classification
# metrics against their torch/scikit-learn
# counter part
# script start;

testthat::test_that(
  desc = "Test that all classification metrics are correctly implemented",
  code = {

    # 0) load functions from
    # {scikit-learn} and {pytorch}
    reticulate::source_python(
      "scikit-learn.py"
    )

    reticulate::source_python(
      "pytorch.py"
    )

    # 1) generate class
    # values
    actual    <- create_factor(balanced = TRUE)
    predicted <- create_factor(balanced = TRUE)

    # 2) generate confusion matrix
    # from {SLmetrics} and {Python}
    sl_matrix <- cmatrix(
      actual    = actual,
      predicted = predicted
    )

    py_matrix <- py_cmatrix(
      actual    = actual,
      predicted = predicted
    )

    # 2.1) test for equality
    # in content
    testthat::expect_true(
      object = set_equal(
        current    = as.table(py_matrix),
        target     = as.table(sl_matrix)
      )
    )

    # 3) test that methods
    # work and returns the same values
    sl_function <- list(
      # specificity methods
      "specificity" = specificity,
      "tnr"         = tnr,
      "selectivity" = selectivity,


      # recall methods;
      "recall"      = recall,
      "sensitivity" = sensitivity,
      "tpr"         = tpr,

      # precision methods
      "precision"   = precision,
      "ppv"         = ppv,

      "fbeta"       = fbeta
    )

    for (i in seq_along(sl_function)) {

      .f <-  sl_function[[i]]

      testthat::expect_true(
        object = set_equal(
          .f(actual, predicted),
          .f(sl_matrix)
        ),
        label = paste(
          "Class-wise metods in", names(sl_function)[i], "not equivalent."
        )
      )

      for (lgl in c(TRUE, FALSE)) {

        testthat::expect_true(
          object = set_equal(
            .f(actual, predicted, micro = lgl),
            .f(sl_matrix, micro = lgl)
          ),
          label = paste(
            "Aggregated methods in", names(sl_function)[i], "not equivalent."
          )
        )

      }


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

      testthat::expect_true(
        object = set_equal(
          .f(actual, predicted),
          as.numeric(.F(actual, predicted))
        ),
        label = paste(
          "Class-wise functions in",
          names(sl_function)[i],
          "not equivalent to {torch} or {scikit-learn}."
        )
      )

      for (lgl in c(TRUE, FALSE)) {

        testthat::expect_true(
          object = set_equal(
            .f(actual, predicted, micro = lgl),
            as.numeric(.F(actual, predicted, average = ifelse(lgl, "micro", "macro")))
          ),
          label = paste(
            "Aggregated functions in",
            names(sl_function)[i],
            "not equivalent to {torch} or {scikit-learn}."
          )
        )

      }


    }


  }
)

# script end;
