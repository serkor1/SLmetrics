# objective: Test OpenMP
# functions

testthat::test_that(
  desc = "Test that `openmp`-family of functions works as expected", code = {

    # 0) skip on CRAN
    testthat::skip_on_cran()

    # 1) check OpenMP availability
    # 1.1) define C++ function
    Rcpp::cppFunction(
      plugins = "openmp",
      code = "
        bool is_available() {
          #ifdef _OPENMP
            return true;
          #else
            return false;
          #endif
          }
          "
    )

    # 1.2) check OpenMP availability
    openmp_available <- is_available()

    # 2) conduct tests conditional 
    # on availability
    if (openmp_available) {
      # 2.1) check that openmp.threads
      # returns the number of available threads
      testthat::expect_true(
        object = openmp.threads() == SLmetrics:::.available_threads(),
        label  = "The number of available threads are not equal."
      )

      # 2.2) check that openmp.threads
      # sets the correct number of threads
      testthat::expect_message(
        object = openmp.threads(2),
        regexp = "Using 2 threads."
      )

      # 2.3) expect messages for 
      # for openmp.on and openmp.off
      testthat::expect_message(openmp.on())
      testthat::expect_message(openmp.off())

    } else {
      # 2.1) check that openmp.threads
      # sends a warning
      testthat::expect_warning(
        object = openmp.threads()
      )

      # 2.2) check that openmp.threads
      # sends a warning
      testthat::expect_warning(
        object = openmp.threads(2)
      )

      # 2.3) expect warnings
      # for openmp.on and openmp.off
      testthat::expect_warning(openmp.on())
      testthat::expect_warning(openmp.off())

    }

  }
)