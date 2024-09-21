# script: Likelihood (Positive, Negative and Diagnost) implementation test
# author: Serkan Korkmaz, serkor1@duck.com
# date: 2024-09-21
# objective: Test that the implementation matches
# that of sklearn
# script start;

testthat::test_that(
  desc = "Test that the implementation matches that of sklearn",
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
    py_score <- py_likelihood(
      actual    = actual,
      predicted = predicted
    )
    # Note: [[1]] is positve!
    py_dor <- py_score[[1]]/py_score[[2]]

    sl_score <- list(
      plr(
        actual    = actual,
        predicted = predicted
      ),
      nlr(
        actual    = actual,
        predicted = predicted
      )
    )

    sl_dor <- sl_score[[1]]/sl_score[[2]]


    # NOTE: this test uses %in% as SLmetrics
    # returns for k-classes while sklearn a
    # total score.

    # 2.2) expect equality
    # NOTE: risk of false here
    # all.equal might be better.
    testthat::expect_true(
      any(
        sl_score[[1]] %in% py_score[[1]],
        sl_score[[2]] %in% py_score[[2]],
        sl_dor %in% py_dor
      )
    )

    # 2.3) expect that its equal
    # to the number of slasses.
    testthat::expect_true(
      all(
        length(sl_score[[1]]) == 3,
        length(sl_score[[2]]) == 3,
        length(sl_dor) == 3
      )
    )

  }
)

# script end;
