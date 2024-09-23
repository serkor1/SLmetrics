# script: fowlkes mallows score
# author: Serkan Korkmaz, serkor1@duck.com
# date: 2024-09-21
# objective: Test fowlkes_mallows_score
# against sklearn
# script start;


testthat::test_that(
  desc = "Test that `fmi()` matches sklearn, and returns a real value",
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


    # 2) calculate the sklearn
    # version of fmi
    py_score <- py_fmi(
      actual    = actual,
      predicted = predicted
    )

    sl_score <- fmi(
      actual    = actual,
      predicted = predicted
    )

    # 3) run tests
    testthat::expect_true(
      all(
        is.numeric(sl_score),
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

