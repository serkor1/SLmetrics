# script: weighted classification metrics
# date: 2024-12-12
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Test that the weighted metrics
# corresponds to target values
# script start;

testthat::test_that(
  desc = "Test that the weighted classification metrics equals {scikit-learn}-equivalents",
  code = {

    # 0) load functions from
    # {scikit-learn} and {pytorch}
    reticulate::source_python(
      "scikit-learn.py"
    )

    reticulate::source_python(
      "pytorch.py"
    )

    source("ref-manual.R")

    # 1) generate class
    # values
    actual    <- create_factor(balanced = TRUE)
    predicted <- create_factor(balanced = TRUE)
    weights   <- runif(n = length(actual))

    # 2) generate confusion matrix
    # from {SLmetrics} and {Python}
    sl_matrix <- cmatrix(
      actual    = actual,
      predicted = predicted,
      w         = weights
    )

    py_matrix <- py_cmatrix(
      actual    = actual,
      predicted = predicted,
      w         = weights
    )

    # 2.1) test for equality
    # in content
    testthat::expect_true(
      object = set_equal(
        current    = as.table(py_matrix),
        target     = as.table(sl_matrix)
      )
    )




  }
)

# script end;