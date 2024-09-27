# script: huber Tests
# author: Serkan Korkmaz, serkor1@duck.com
# date: 2024-08-24
# objective: Test that the implementation
# matches that of pytorch
# script start;

testthat::test_that(
  desc = "`huber()`-function matches that of pytorch and returns non-zero postive values",
  code = {

    # 0) source the python
    # program

    reticulate::source_python(
      "ref-pytorch.py"
    )

    # 1) generate values
    # from a normal distribution
    actual <- rnorm(
      n = 1e2
    )

    predicted <- actual + rnorm(
      n = 1e2
    )

    for (delta in c(1,2,3)) {

      # 2) generate score
      py_score <- py_huber(
        actual = actual,
        predicted = predicted,
        delta = delta
      )

      sl_score <- huberloss(
        actual = actual,
        predicted = predicted,
        delta = delta
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


  }
)

testthat::test_that(
  desc = "`whuber()`-function matches that of pytorch and returns non-zero postive values",
  code = {


    # 0) source the python
    # program


    reticulate::source_python(
      "ref-pytorch.py"
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

    for (delta in c(1,2,3)) {


      # 2) generate score
      py_score <- py_huber(
        actual    = actual,
        predicted = predicted,
        w         = w,
        delta     = delta
      )

      sl_score <- whuberloss(
        actual    = actual,
        predicted = predicted,
        w         = w,
        delta     = delta
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


  }
)

# script end;
