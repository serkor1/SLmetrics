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
        x = 1:2,
        size = 1e3,
        replace = TRUE
      ),
      levels = c(1:2),
      labels = letters[1:2]
    )

    # 1.2) predicted
    # values
    predicted <- factor(
      x = sample(
        1:2,
        size = 1e3,
        replace = TRUE
      ),
      levels = c(1:2),
      labels = letters[1:2]
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
      all(
        all.equal(
          target  = py_score[[1]],
          current = sl_score[[1]][1],
          tolerance = 1e-3,
          check.attributes = FALSE,
          check.class = FALSE
        ),
        all.equal(
          target  = py_score[[2]],
          current = sl_score[[2]][1],
          tolerance = 1e-3,
          check.attributes = FALSE,
          check.class = FALSE

        ),
        all.equal(
          target  = py_dor,
          current = sl_dor[1],
          tolerance = 1e-9,
          check.attributes = FALSE,
          check.class = FALSE

        )
      )
    )

    # 2.3) expect that its equal
    # to the number of slasses.
    testthat::expect_true(
      all(
        length(sl_score[[1]]) == 2,
        length(sl_score[[2]]) == 2,
        length(sl_dor) == 2
      )
    )

    # 2.4) finally expect that
    # plr/nlr = dor built-in
    testthat::expect_true(
      all.equal(
        target = dor(
          actual,
          predicted,
          aggregate = FALSE
        ),
        current = sl_dor,
        tolerance = 1e-9,
        check.attributes = FALSE,
        check.class = FALSE
      )
    )

    # 2.5) check for micro-averaged
    # DOR
    manual_dor <- plr(
      actual = actual,
      predicted = predicted,
      aggregate = TRUE
    ) / nlr(
      actual = actual,
      predicted = predicted,
      aggregate = TRUE
    )

    testthat::expect_true(
      all.equal(
        target = dor(
          actual,
          predicted,
          aggregate = TRUE
        ),
        current = manual_dor,
        tolerance = 1e-9,
        check.attributes = FALSE,
        check.class = FALSE
      )
    )

  }
)

# script end;
