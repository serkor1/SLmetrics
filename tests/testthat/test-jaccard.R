# script: Jaccard Score
# date: 2024-09-16
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Test the Jaccard Index and
# its aliasses
# script start;

testthat::test_that(
  desc = "Test that `jaccard()` and aliases works as intended (Has to return either a sinlge value or k values",
  code = {

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


    # 2) evaluate the
    # vectors using
    # `jaccard()` and family
    # without aggregation
    testthat::expect_true(
      length(
        unique(
          lapply(
            X = list(
              jaccard,
              csi,
              tscore
            ),
            FUN = function(f) {

              # 2.1) evaluate the
              # performance
              output <- f(actual, predicted)

              # 2.2) check that the
              # values are numeric
              testthat::expect_true(
                is.numeric(output)
              )

              # 2.2) check that no
              # values are NA.
              testthat::expect_true(
                !any(is.na(output))
              )

              # 3) return
              # all values
              output

            }
          )
        )
      ) == 1
    )

    # 3) evaluate the
    # vectors using
    # `jaccard()` and family
    # with aggregation
    testthat::expect_true(
      length(
        unique(
          lapply(
            X = list(
              jaccard,
              csi,
              tscore
            ),
            FUN = function(f) {

              # 2.1) evaluate the
              # performance
              output <- f(actual, predicted, aggregate = TRUE)

              # 2.2) check that the
              # values are numeric
              testthat::expect_true(
                is.numeric(output)
              )

              # 2.2) check that no
              # values are NA.
              testthat::expect_true(
                !any(is.na(output))
              )

              # 3) return
              # all values
              output

            }
          )
        )
      ) == 1
    )









  }
)


# script end;
