# script: Confusion Matrix
# date: 2024-10-05
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Test that the associated methods
# of the cmatrix works as intended
# script start;

testthat::test_that(
  desc = "Test that the methods associated with the `cmatrix()`-function works as intended",
  code = {

    # 1) generate confusion
    # matrix
    confusion_matrix <- cmatrix(
      actual    = create_factor(),
      predicted = create_factor()
    )

    # 2) test that summary
    # works without any conditions
    testthat::expect_no_condition(
      invisible(
        summary(confusion_matrix)
      )

    )

    # 3) test that plot
    # works without any conditions
    testthat::expect_no_condition(
      invisible(
        plot(
          confusion_matrix
        )
      )
    )
  }
)

# script end;
