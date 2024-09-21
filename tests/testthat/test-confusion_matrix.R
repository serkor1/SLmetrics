# script: Test implementation confusion matrix
# author: Serkan Korkmaz, serkor1@duck.com
# date: 2024-09-21
# objective: Check that the implementation
# matches that of sklearn
# script start;
# start of script; ###

testthat::test_that(
  desc = "Test that `cmatrix()` matches that of sklearn",
  code = {

    # 0) source the python
    # program
    reticulate::source_python(
      "scikit-learn.py"
    )

    # 1) create two vectors
    # of classes where one class
    # has not been predicted at all

    # 1.1) actual
    # values
    actual <- factor(
      x = sample(
        x = 1:3,
        size = 1e3,
        replace = TRUE,
        prob = c(0,0.5,0.5)
      ),
      levels = c(1:3),
      labels = letters[1:3]
    )

    # 1.2) predicted
    # values
    predicted <- factor(
      x = sample(
        1:3,
        size = 1e3,
        replace = TRUE,
        prob = c(0,0.5,0.5)
      ),
      levels = c(1:3),
      labels = letters[1:3]
    )


    # 2) test that;
    py_matrix <- py_cmatrix(
      actual,
      predicted
    )

    sl_matrix <- cmatrix(
      actual,
      predicted
    )

    testthat::expect_true(
      all(
        dim(sl_matrix) %in% c(3,3),
        sapply(sl_matrix, inherits, "numeric"),
        colnames(sl_matrix) %in% letters[1:3],
        py_matrix %in% sl_matrix
      )
    )

  }
)

# end of script; ###
