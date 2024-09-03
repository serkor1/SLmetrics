# script: test-confusion_matrix
# author: Serkan Korkmaz
# objective: Test that the cofidence interval
# returns a named matrix based on number
# of levels and names it according to the
# labels
# date: 2024-09-03
# start of script; ###

testthat::test_that(
  desc = "Test confusion_matrix and its returned values",
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
          n = 10,
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
      testthat::expect_no_error(
        object = confusion_matrix(
          actual,
          predicted
        )
      )

    }

  }
)

# end of script; ###
