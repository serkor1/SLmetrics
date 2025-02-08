# objective: Test that the S3 methods
# works and returns the same values
# using factors and confusion matrix with default calls.

testthat::test_that(
  desc = "Test that S3 methods returns the same values for classification metrics (balanced)", code = {

    testthat::skip_on_cran()

    # 1) generate class
    # values
    actual    <- create_factor(balanced = TRUE)
    predicted <- create_factor(balanced = TRUE)
    w         <- runif(n = length(actual))

    # 2) generate confusion matrix
    # from {SLmetrics} and {Python}
    sl_matrix <- cmatrix(
      actual    = actual,
      predicted = predicted
    )

    sl_wmatrix <- weighted.cmatrix(
      actual    = actual,
      predicted = predicted,
      w         = w
    )

    py_matrix <- py_cmatrix(
      actual    = actual,
      predicted = predicted
    )

    py_wmatrix <- py_cmatrix(
      actual    = actual,
      predicted = predicted,
      w         = w
    )

    # 3) test that the functions
    # returns the same value regardless
    # of method
    for (i in seq_along(sl_classification)) {

      # 3.1) extract function
      # and pass into methods
      .f <-  sl_classification[[i]]

      # 3.2) expect these to
      # be equal
      testthat::expect_true(
        object = set_equal(
          as.numeric(.f(actual, predicted)),
          as.numeric(.f(sl_matrix))
        ),
        label = paste(
          "Class-wise metods in", names(sl_classification)[i], "not equivalent."
        )
      )

    }

    # 4) test that the functions
    # returns the same value regardless
    # of method for weighted classification
    for (i in seq_along(sl_classification)) {
      name <- names(sl_classification)[i]
      
      # Check if the name exists in both lists
      if (name %in% names(sl_wclassification)) {
        # Extract corresponding functions
        .f <- sl_wclassification[[name]]
        .F <- sl_classification[[name]]
        
        # Ensure these are expected to be equal
        testthat::expect_true(
          object = set_equal(
            as.numeric(.f(actual, predicted, w = w)),
            as.numeric(.F(sl_wmatrix))
          ),
          label = paste(
            "Weighted class-wise methods in", name, "not equivalent."
          )
        )
      }
    }

    # 5) test that the functions
    # returns a differemt value regardless
    # of method for weighted classification
    for (i in seq_along(sl_classification)) {
      name <- names(sl_classification)[i]
      
      # Check if the name exists in both lists
      if (name %in% names(sl_wclassification)) {
        # Extract corresponding functions
        .f <- sl_wclassification[[name]]
        .F <- sl_classification[[name]]
        
        # Ensure these are expected to be equal
        # NOTE: if they are not equal it wont return
        # a logical value.
        testthat::expect_false(
          object = is.logical(set_equal(
            as.numeric(.f(actual, predicted, w = w)),
            as.numeric(.F(sl_matrix))
          )),
          label = paste(
            "Weighted and unweighted class-wise methods in", name, "are equivalent."
          )
        )
      }
    }

})


testthat::test_that(
  desc = "Test that S3 methods returns the same values for classification metrics (imbalanced)", code = {

    testthat::skip_on_cran()

    # 1) generate class
    # values
    actual    <- create_factor(balanced = FALSE)
    predicted <- create_factor(balanced = FALSE)
    w         <- runif(n = length(actual))

    # 2) generate confusion matrix
    # from {SLmetrics} and {Python}
    sl_matrix <- cmatrix(
      actual    = actual,
      predicted = predicted
    )

    sl_wmatrix <- weighted.cmatrix(
      actual    = actual,
      predicted = predicted,
      w         = w
    )

    py_matrix <- py_cmatrix(
      actual    = actual,
      predicted = predicted
    )

    py_wmatrix <- py_cmatrix(
      actual    = actual,
      predicted = predicted,
      w         = w
    )

    # 3) test that the functions
    # returns the same value regardless
    # of method
    for (i in seq_along(sl_classification)) {

      # 3.1) extract function
      # and pass into methods
      .f <-  sl_classification[[i]]

      # 3.2) expect these to
      # be equal
      testthat::expect_true(
        object = set_equal(
          as.numeric(.f(actual, predicted)),
          as.numeric(.f(sl_matrix))
        ),
        label = paste(
          "Unweighted class-wise metods in", names(sl_classification)[i], "not equivalent."
        )
      )

    }

    # 4) test that the functions
    # returns the same value regardless
    # of method for weighted classification
    for (i in seq_along(sl_classification)) {
      name <- names(sl_classification)[i]
      
      # Check if the name exists in both lists
      if (name %in% names(sl_wclassification)) {
        # Extract corresponding functions
        .f <- sl_wclassification[[name]]
        .F <- sl_classification[[name]]
        
        # Ensure these are expected to be equal
        testthat::expect_true(
          object = set_equal(
            as.numeric(.f(actual, predicted, w = w)),
            as.numeric(.F(sl_wmatrix))
          ),
          label = paste(
            "Weighted class-wise methods in", name, "not equivalent."
          )
        )
      }
    }

    # 5) test that the functions
    # returns a differemt value regardless
    # of method for weighted classification
    for (i in seq_along(sl_classification)) {
      name <- names(sl_classification)[i]
      
      # Check if the name exists in both lists
      if (name %in% names(sl_wclassification)) {
        # Extract corresponding functions
        .f <- sl_wclassification[[name]]
        .F <- sl_classification[[name]]
        
        # Ensure these are expected to be equal
        # NOTE: if they are not equal it wont return
        # a logical value.
        testthat::expect_false(
          object = is.logical(set_equal(
            as.numeric(.f(actual, predicted, w = w)),
            as.numeric(.F(sl_matrix))
          )),
          label = paste(
            "Weighted and unweighted class-wise methods in", name, "are equivalent."
          )
        )
      }
    }

})


