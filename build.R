# script: Build Package
# author: Serkan Korkmaz, serkor1@duck.com
# date: 2024-10-04
# objective: This builds the package
# without recompiling the Rcpp Attributes
# script start;

# 1) roxygenize documentation
# using {roxygen2}
roxygen2::roxygenize(
  clean   = TRUE,
  roclets = c("collate", "namespace", "rd")
)

# 2) r-cmd-check
rcmdcheck::rcmdcheck(
  args = c(
    "--as-cran",
    "--no-tests"
  )
)

# 3) run testthat
testthat::test_local()


# script end;
