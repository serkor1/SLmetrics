# objective: Test that OpenMP
# is well-behaved

testthat::test_that(
  desc = "Test OpenMP-family of functions", code = {

    testthat::skip_on_cran()

    # test if OpenMP is available
    # if available the value will be different
    # from 0
    openmp_available <- SLmetrics:::.available_threads() != 0

    if (openmp_available) {

      testthat::expect_true(
        object = is.numeric(openmp.threads()) | is.integer(openmp.threads())
      )

      testthat::expect_condition(
        object = openmp.threads(1),
        regexp = "Using 1 threads."
      )

      testthat::expect_condition(
        object = openmp.on(),
        regexp = "OpenMP enabled!"
      )

      testthat::expect_condition(
        object = openmp.off(),
        regexp = "OpenMP disabled!"
      )

    } else  {

      testthat::expect_true(
        object = is.null(openmp.threads())
      )

      testthat::expect_condition(
        object = openmp.threads(1),
        regexp = "OpenMP is not available on your system!"
      )

      testthat::expect_condition(
        object = openmp.on(),
        regexp = "OpenMP is not available on your system!"
      )

      testthat::expect_condition(
        object = openmp.off(),
        regexp = "OpenMP is not available on your system!"
      )


    }
    


  }
)