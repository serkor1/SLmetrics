# script: Documenting the {pkg}
# date: 2024-10-10
# author: Serkan Korkmaz, serkor1@duck.com
# objective: The documentation needs a few additional
# steps as it is currently overwriting RcppExports.R
# twice.
# script start;


# 0) Compile attributes
# to avoid trouble when running
# document more than once.
Rcpp::compileAttributes()

# 1) First Documentation
# NOTE: This builds the package
# before it does anything else if
# there is changes in .dll files
#
# As of now I have not found a way around
# this.
suppressMessages(
  roxygen2::roxygenize(
    clean   = TRUE,
    roclets = c("collate", "namespace", "rd")
  )
)

# 2) After the the initial
# roxygenize run; it is necessary to
# modify RcppExports.R so the function
# arg naming can be done.
source("tools/modifyRcppExports.R")

# 3) After the RcppExports.R
# has been modified, the Roxygenize can be run
# again to apply the changes made
# on RcppExports.
roxygen2::roxygenize(
  clean   = TRUE,
  roclets = c("collate", "namespace", "rd")
)

# 4) Render README and NEWS
# while documenting
rmarkdown::render(
  input = "README.Rmd",
  output_format = "github_document",
  clean = TRUE
)

rmarkdown::render(
  input = "NEWS.Rmd",
  output_format = "github_document",
  clean = TRUE
)

# script end;
