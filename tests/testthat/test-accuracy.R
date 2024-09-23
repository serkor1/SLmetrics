# script: Test implementation accuracy
# author: Serkan Korkmaz, serkor1@duck.com
# date: 2024-09-21
# objective: Check that the implementation
# matches that of sklearn
# script start;

testthat::test_that(
  desc = "Test that `accuracy()` matches that of sklearn",
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

    for (lgl in c(TRUE, FALSE)) {

      py_score <- py_accuracy(
        actual    = actual,
        predicted = predicted
      )

      sl_score <- accuracy(
        actual    = actual,
        predicted = predicted
      )

      # 1) expect all true
      # for numeric and
      # no NAs
      testthat::expect_true(
        all(
          is.numeric(sl_score),
          if (lgl)
            !any(is.na(sl_score))
          else
            TRUE
        )
      )

      testthat::expect_true(
        all.equal(
          target  = na.omit(sl_score),
          current = py_score,
          tolerance =  1e-9,
          check.attributes = FALSE,
          check.class = FALSE
        )
      )

      if (!lgl) {

        # If lgl = FALSE the macro average
        # is found by mean(foo(..., aggregate = FALSE))


        testthat::expect_true(
          all.equal(
            target  = mean(
              sl_score,
              na.rm = TRUE
            ),
            current =  py_accuracy(
              actual    = actual,
              predicted = predicted
            ),
            tolerance =  1e-9,
            check.attributes = FALSE,
            check.class = FALSE

          )
        )

      }

    }


  }
)


# script end;
