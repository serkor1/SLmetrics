# script: Internals
# date: 2024-09-29
# author: Serkan Korkmaz, serkor1@duck.com
# objective: This function tests
# the validity of the internal functions
# script start;

testthat::test_that(
  desc = "Test that internal functions are correctly calculating values",
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

    for (average in c("micro", "macro")) {

      current_values <- sapply(
        list(
          .accuracy,
          .baccuracy,
          .specificity,
          .sensitivity,
          .precision
        ),
        FUN = function(.f) {

          tryCatch(
            .f(
              cmatrix(actual, predicted),
              micro = average == "micro"
            ),
            error = function(cond) {

              .f(
                cmatrix(actual, predicted)
              )

            }
          )

        }
      )

      target_values <- sapply(
        list(
          accuracy,
          baccuracy,
          specificity,
          sensitivity,
          precision
        ),
        FUN = function(.f) {

          tryCatch(
            .f(
              actual,
              predicted,
              aggregate = average == "micro"
            ),
            error = function(cond) {

              .f(
                actual,
                predicted
              )

            }
          )


        }
      )

      if (average == "macro") {

        target_values <- sapply(
          target_values,
          mean
        )

      }

      testthat::expect_true(
        all.equal(
          current = current_values,
          target  = target_values,
          check.attributes = FALSE,
          check.class = FALSE
        )
      )


    }



  }
)

# script end;
