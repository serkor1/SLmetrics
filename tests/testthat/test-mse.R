# script: mse Tests
# author: Serkan Korkmaz, serkor1@duck.com
# date: 2024-08-24
# objective: Test that the implementation
# matches that of sklearn
# script start;

testthat::test_that(
  desc = "`mse()`-function matches that of sklearn and returns non-zero postive values",
  code = {

    # 0) source the python
    # program
    reticulate::source_python(
      "scikit-learn.py"
    )

    # 1) generate values
    # from a normal distribution
    actual <- rnorm(
      n = 1e2
    )

    predicted <- actual + rnorm(
      n = 1e2
    )

    # 2) generate score
    py_score <- py_mse(
      actual = actual,
      predicted = predicted
    )

    sl_score <- mse(
      actual = actual,
      predicted = predicted
    )

    # 3) test that
    testthat::expect_true(
      all(
        sl_score > 0,
        length(sl_score) == 1,
        !is.na(sl_score)
      )
    )

    testthat::expect_true(
      all.equal(
        target  = py_score,
        current = sl_score,
        tolerance =  1e-9,
        check.attributes = FALSE,
        check.class = FALSE
      )
    )

  }
)

testthat::test_that(
  desc = "`wmse()`-function matches that of sklearn and returns non-zero postive values",
  code = {

    # 0) source the python
    # program
    reticulate::source_python(
      "scikit-learn.py"
    )

    # 1) generate values
    # from a normal distribution
    actual <- rnorm(
      n = 1e2
    )

    predicted <- actual + rnorm(
      n = 1e2
    )


    w <- runif(
      n = 1e2
    )

    # 2) generate score
    py_score <- py_mse(
      actual    = actual,
      predicted = predicted,
      w         = w
    )

    sl_score <- wmse(
      actual    = actual,
      predicted = predicted,
      w         = w
    )

    # 3) test that
    testthat::expect_true(
      all(
        sl_score > 0,
        length(sl_score) == 1,
        !is.na(sl_score)
      )
    )

    testthat::expect_true(
      all.equal(
        target  = py_score,
        current = sl_score,
        tolerance =  1e-9,
        check.attributes = FALSE,
        check.class = FALSE
      )
    )

  }
)

# script end;
