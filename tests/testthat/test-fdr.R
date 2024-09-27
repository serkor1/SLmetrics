# script: False Discovery Rate
# date: 2024-09-25
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Check wether
# the function returns sensible
# values that equals the manually calcualted
# FDR values
# script start;

testthat::test_that(
  desc = "Test that the `fdr()`-function returns a sensible and correct value",
  code = {

    # 1) create two vectors
    # of classes

    # 1.1) actual
    # values
    actual <- factor(
      x = sample(
        x = 1:2,
        size = 1e3,
        replace = TRUE,
        prob = c(0.25,0.75)
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
        replace = TRUE,
        prob = c(0.6,0.4)
      ),
      levels = c(1:2),
      labels = letters[1:2]
    )

    # 2) calculate target values
    #
    # 2.1) generate confusion
    # matrices
    t_matrix <- matrix(
      table(
        actual,
        predicted
      ),
      byrow = FALSE,
      nrow = 2,
      ncol = 2
    )

    c_matrix <- cmatrix(
      actual,
      predicted
    )

    # 2.2) test that they
    # are equal
    testthat::expect_true(
      all.equal(
        target  = t_matrix,
        current = c_matrix,
        check.attributes = FALSE,
        check.class = FALSE
      )
    )

    # 3) test that all
    # values are equal
    target_fdr <- (colSums(t_matrix) - diag(t_matrix)) / colSums(t_matrix)
    sl_fdr     <- fdr(actual,predicted)

    # 3.1) conduct the
    # test
    testthat::expect_true(
      all.equal(
        target  = target_fdr,
        current = sl_fdr,
        check.attributes = FALSE,
        check.class = FALSE
      )
    )


  }
)

# script end;
