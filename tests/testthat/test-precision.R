testthat::test_that(
  desc = "Test that `precision()`-function runs smoothly",
  code = {

    for (i in 2:10) {

      # 1) generate count vector
      # of predictions and actual
      # values

      # 1.1) generate labels
      # based on letters
      unique_labels <- letters[1:(i+1)]

      # 1.2) generate predicted and
      # actual vectors of labels

      predicted <- actual <- factor(
        x = rbinom(
          n = 20,
          # size controls the
          # number of
          size = i,
          prob = 0.5
        ),
        levels = 0:i,
        labels = unique_labels
      )


      # 2) generate the confusion
      # matrix and expect that it runs
      # without errors
      testthat::expect_length(
        testthat::expect_no_error(
          object = precision(
            actual,
            predicted,
            aggregate = FALSE
          )
        ),
        n = i + 1
      )

      testthat::expect_length(
        testthat::expect_no_error(
          object = precision(
            actual,
            predicted,
            aggregate = TRUE
          )
        ),
        n = 1
      )

    }

  }
)
