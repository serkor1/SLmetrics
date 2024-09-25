# script: Test MPE
# author: Serkan Korkmaz, serkor1@duck.com
# date: 2024-09-25
# objective: This has a local target. It should return
# the appropriate values.
# script start;

testthat::test_that(
  desc = "Test that the `mpe()`-function returns sensible values",
  code = {

    # 1) generate values
    # from a normal distribution
    actual <- rnorm(
      n = 1e2
    )

    predicted <- actual + rnorm(
      n = 1e2
    )

    w <- rbeta(
      n = 1e2,
      shape1 = 10,
      shape2 = 2
    )

    for (lgl in c(TRUE, FALSE)) {

      if (lgl) {
        score <- mpe(
          actual    = actual,
          predicted = predicted
        )

        target <- mean((actual - predicted) / actual)
      } else {
        score <- wmpe(
          actual    = actual,
          predicted = predicted,
          w         = w
        )

        target  <- weighted.mean(
          x = (actual - predicted) / actual,
          w = w)
      }

      testthat::expect_true(
        all(
          # check that it returns
          # a single score
          length(score) == 1,

          # check that it is
          # not NA
          !is.na(score),

          # check that it is
          # numeric
          is.numeric(score),

          # check that it is equal
          # to the target
          all.equal(
            target = target,
            current = score,
            tolerance = 1e-9,
            check.attributes = TRUE,
            check.class = TRUE
          )
        )
      )
    }
  }
)

# script end;
