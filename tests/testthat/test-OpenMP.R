# objective: Test OpenMP
# functions

testthat::test_that(
  desc = "Test that `openmp`-family of functions works as expected", code = {

    # 0) skip on CRAN
    testthat::skip_on_cran()

    # 1) check OpenMP availability
    # 1.1) define C++ function (Obsolete)
    #
    # NOTE: This counts the number of recognized threads
    # at runtime, #ifdef _OPENMP essentially just checks
    # if the compiler is *OpenMP ready* - so if your system
    # is not correctly set up to use OpenMP #ifdef _OPENMP will not fail, 
    # but the parallel execution will be done on a single thread; which is essentially
    # the same as not have OpenMP.
    #
    # The above may be pure bullshit.
    available <- openmp_available()

    # 2) conduct tests conditional 
    # on availability
    if (available) {
      # 2.1) check that openmp.threads
      # returns the number of available threads
      testthat::expect_true(
        object = openmp.threads() == available_threads(),
        label  = "The number of available threads are not equal."
      )

      # 2.2) check that openmp.threads
      # sets the correct number of threads
      testthat::expect_message(
        object = openmp.threads(2),
        regexp = "Using 2 threads.",
        label  = "Setting openmp.threads(2) in branch: available" 
      )

      # 2.3) expect messages for 
      # for openmp.on and openmp.off
      testthat::expect_message(openmp.on(), label = "openmp.on() in branch: available")
      testthat::expect_message(openmp.off(), label = "openmp.off() in branch: available")

    } else {
      # 2.1) check that openmp.threads
      # sends a warning
      testthat::expect_warning(
        object = openmp.threads(),
        label  = "Number of available threads in branch: !available"
      )

      # 2.2) check that openmp.threads
      # sends a warning
      testthat::expect_warning(
        object = openmp.threads(2),
        label  = "Setting openmp.threads(2) (branch: !available)" 
      )

      # 2.3) expect warnings
      # for openmp.on and openmp.off
      testthat::expect_warning(openmp.on(), label = "openmp.on() in branch: !available")
      testthat::expect_warning(openmp.off(), label = "openmp.off() in branch: !available")

    }

  }
)