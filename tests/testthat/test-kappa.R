# script: Cohens Kappa
# author: Serkan Korkmaz, serkor1@duck.com
# date: 2024-09-21
# objective: Test that the kappa statistic
# matches that of sklearn
# script start;

testthat::test_that(
  desc = "Test that `kappa()`-function matches that of sklearn for all weights",
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
    for (i in c(0,1,2)) {

      py_score <- py_kappa(
        actual    = actual,
        predicted = predicted,
        penalty   = switch(
          i,
          `0` = NULL,
          `1`  = "linear",
          `2`  = "quadratic"
        )
      )

      sl_score <- kappa(
        actual = actual,
        predicted = predicted,
        beta = i
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

  }
)

# script end;
