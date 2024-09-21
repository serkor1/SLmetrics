# script: Matthews Correlation Coefficient
# author: Serkan Korkmaz, serkor1@duck.com
# date: 2024-09-21
# objective: Check that the implementation
# matches that of sklearn
# script start;

testthat::test_that(
  desc = "Test that `mcc()` matches sklearn, and returns a single value",
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

    # 2) test that
    py_score <- py_mcc(
      actual = actual,
      predicted = predicted
    )

    sl_score <- mcc(
      actual    = actual,
      predicted = predicted
    )

    # expect all true
    # for numeric and
    # no NAs
    testthat::expect_true(
      all(
        is.numeric(sl_score),
        length(sl_score) == 1,
        !is.na(sl_score)
      )
    )

    testthat::expect_true(
      all.equal(
        target  = sl_score,
        current = py_score,
        tolerance =  1e-9,
        check.attributes = FALSE,
        check.class = FALSE
      )
    )

  }
)

# script end;
